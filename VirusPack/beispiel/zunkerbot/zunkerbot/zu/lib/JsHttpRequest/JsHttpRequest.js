/**
 * JsHttpRequest: JavaScript "AJAX" data loader.
 * (C) 2006 Dmitry Koterov, http://forum.dklab.ru/users/DmitryKoterov/
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * See http://www.gnu.org/copyleft/lesser.html
 *
 * Do not remove this comment if you want to use script!
 * Не удаляйте данный комментарий, если вы хотите использовать скрипт!
 *
 * This library tries to use XMLHttpRequest (if available), and on 
 * failure - use dynamically created <script> elements. Backend code
 * is the same for both cases. Library also supports file uploading;
 * in this case it uses FORM+IFRAME-based loading.
 *
 * @author Dmitry Koterov 
 * @version 4.14
 */

function JsHttpRequest() { this._construct() }
(function() { // to create local-scope variables
    var COUNT       = 0;
    var PENDING     = {};
    var CACHE       = {};

    // Called by server script on data load. Static.
    JsHttpRequest.dataReady = function(id, text, js) {
        var undef;
        var th = PENDING[id];
        delete PENDING[id];
        if (th) {
            delete th._xmlReq;
            if (th.caching && th.hash) CACHE[th.hash] = [text, js];
            th._dataReady(text, js);
        } else if (th !== false) {
            throw "JsHttpRequest.dataReady(): unknown pending id: " + id;
        }
    }

    // Simple interface for most popular use-case.
    JsHttpRequest.query = function(url, content, onready, nocache) {
        var req = new JsHttpRequest();
        req.caching = !nocache;
        req.onreadystatechange = function() {
            if (req.readyState == 4) {
                onready(req.responseJS, req.responseText);
            }
        }
        req.open(null, url, true);
        req.send(content);
    },
    
    JsHttpRequest.prototype = {
        // Standard properties.
        onreadystatechange: null,
        readyState:         0,
        responseText:       null,
        responseXML:        null,
        status:             200,
        statusText:         "OK",
        // JavaScript response array/hash
        responseJS:         null,

        // Additional properties.
        session_name:       "PHPSESSID",  // set to SID cookie or GET parameter name
        caching:            false,        // need to use caching?
        loader:             null,         // loader to use ('form', 'script', 'xml'; null - autodetect)

        // Internals.
        _span:              null,
        _id:                null,
        _xmlReq:            null,
        _openArg:           null,
        _reqHeaders:        null,
        _maxUrlLen:         2000,

        dummy: function() {}, // empty constant function for ActiveX leak minimization

        abort: function() {
            if (this._xmlReq) {
                this._xmlReq.abort();
                this._xmlReq = null;
            }
            this._cleanupScript();
            this._changeReadyState(4, true); // 4 in IE & FF on abort() call; Opera does not change to 4.
        },

        open: function(method, url, asyncFlag, username, password) {
            // Append SID to original URL.
            var sid = this._getSid();
            if (sid) url += (url.indexOf('?')>=0? '&' : '?') + this.session_name + "=" + this.escape(sid);
            this._openArg = {
                method:     (method||'').toUpperCase(),
                url:        url,
                asyncFlag:  asyncFlag,
                username:   username != null? username : '',
                password:   password != null? password : ''
            };
            this._id = null;
            this._xmlReq = null;
            this._reqHeaders = [];
            this._changeReadyState(1, true); // compatibility with XMLHttpRequest
            return true;
        },
        
        send: function(content) {
            this._changeReadyState(1, true); // compatibility with XMLHttpRequest

            var id = (new Date().getTime()) + "" + COUNT++;
            var url = this._openArg.url; 

            // Prepare to build QUERY_STRING from query hash.
            var queryText = [];
            var queryElem = [];
            if (!this._hash2query(content, null, queryText, queryElem)) return;

            var loader = (this.loader||'').toLowerCase();
            var method = this._openArg.method;
            var xmlReq = null;
            if (queryElem.length && !loader) {
                // Always use form loader if we have at least one form element.
                loader = 'form';
            } else {
                // Try to obtain XML request object.
                xmlReq = this._obtainXmlReq(id, url)
            }

            // Full URL if parameters are passed via GET.
            var fullGetUrl = url + (url.indexOf('?')>=0? '&' : '?') + queryText.join('&');

            // Solve hashcode BEFORE appending ID and check if cache is already present.
            this.hash = null;
            if (this.caching && !queryElem.length) {
                this.hash = fullGetUrl;
                if (CACHE[this.hash]) {
                    var c = CACHE[this.hash];
                    this._dataReady(c[0], c[1]);
                    return false;
                }
            }

            // Detect loader and method. (Yes, lots of code and conditions!)
            var canSetHeaders = xmlReq && (window.ActiveXObject || xmlReq.setRequestHeader); 
            if (!loader) {
                // Auto-detect loader.
                if (xmlReq) {
                    // Can use XMLHttpRequest.
                    loader = 'xml';
                    switch (method) {
                        case "POST":
                            if (!canSetHeaders) {
                                // Use POST method. Pass query in request body.
                                // Opera 8.01 does not support setRequestHeader, so no POST method.
                                loader = 'form';
                            }
                            break;
                        case "GET":
                            // Length of the query is checked later.
                            break;
                        default:
                            // Method is not set: auto-detect method.
                            if (canSetHeaders) {
                                method = 'POST';
                            } else {
                                if (fullGetUrl.length > this._maxUrlLen) {
                                    method = 'POST';
                                    loader = 'form';
                                } else {
                                    method = 'GET';
                                }
                            }
                    }
                } else {
                    // Cannot use XMLHttpRequest.
                    loader = 'script';
                    switch (method) {
                        case "POST":
                            loader = 'form';
                            break;
                        case "GET":
                            // Length of the query is checked later.
                            break;
                        default:
                            if (fullGetUrl.length > this._maxUrlLen) {
                                method = 'POST';
                                loader = 'form';
                            } else {
                                method = 'GET';
                            }
                    }
                }
            } else if (!method) {
                // Loader is pre-defined, but method is not set.
                switch (loader) {
                    case 'form':
                        method = 'POST';
                        break;
                    case 'script':
                        method = 'GET';
                        break;
                    default:
                        if (canSetHeaders) {
                            method = 'POST';
                        } else {
                            method = 'GET';
                        }
                }
            }

            // Correct GET URL.
            var requestBody = null;
            if (method == 'GET') {
                url = fullGetUrl;
                if (url.length > this._maxUrlLen) return this._error('Cannot use so long query (URL is ' + url.length + ' byte(s) length) with GET request.');
            } else if (method == 'POST') {
                requestBody = queryText.join('&');
            } else {
                return this._error('Unknown method: ' + method + '. Only GET and POST are supported.');
            }

            // Append loading ID to URL: a=aaa&b=bbb&<id>
            url = url + (url.indexOf('?')>=0? '&' : '?') + 'JsHttpRequest=' + id + '-' + loader;

            // Save loading script.
            PENDING[id] = this;

            // Send the request.
            switch (loader) {
                case 'xml':
                    // Use XMLHttpRequest.
                    if (!xmlReq) return this._error('Cannot use XMLHttpRequest or ActiveX loader: not supported');
                    if (method == "POST" && !canSetHeaders) return this._error('Cannot use XMLHttpRequest loader or ActiveX loader, POST method: headers setting is not supported');
                    if (queryElem.length) return this._error('Cannot use XMLHttpRequest loader: direct form elements using and uploading are not implemented');
                    this._xmlReq = xmlReq;
                    var a = this._openArg;
                    this._xmlReq.open(method, url, a.asyncFlag, a.username, a.password);
                    if (canSetHeaders) {
                        // Pass pending headers.
                        for (var i=0; i<this._reqHeaders.length; i++)
                            this._xmlReq.setRequestHeader(this._reqHeaders[i][0], this._reqHeaders[i][1]);
                        // Set non-default Content-type. We cannot use 
                        // "application/x-www-form-urlencoded" here, because 
                        // in PHP variable HTTP_RAW_POST_DATA is accessible only when 
                        // enctype is not default (e.g., "application/octet-stream" 
                        // is a good start). We parse POST data manually in backend 
                        // library code.
                        this._xmlReq.setRequestHeader('Content-Type', 'application/octet-stream');
                    }
                    // Send the request.
                    return this._xmlReq.send(requestBody);

                case 'script':
                    // Create <script> element and run it.
                    if (method != 'GET') return this._error('Cannot use SCRIPT loader: it supports only GET method');
                    if (queryElem.length) return this._error('Cannot use SCRIPT loader: direct form elements using and uploading are not implemented');
                    this._obtainScript(id, url);
                    return true;

                case 'form':
                    // Create & submit FORM.
                    if (!this._obtainForm(id, url, method, queryText, queryElem)) return null;
                    return true;

                default:
                    return this._error('Unknown loader: ' + loader);
            }
        },

        getAllResponseHeaders: function() {
            if (this._xmlReq) return this._xmlReq.getAllResponseHeaders();
            return '';
        },
            
        getResponseHeader: function(label) {
            if (this._xmlReq) return this._xmlReq.getResponseHeader(label);
            return '';
        },

        setRequestHeader: function(label, value) {
            // Collect headers.
            this._reqHeaders[this._reqHeaders.length] = [label, value];
        },


        //
        // Internal functions.
        //

        // Constructor.
        _construct: function() {},

        // Do all work when data is ready.
        _dataReady: function(text, js) { with (this) {
            if (text !== null || js !== null) {
                status = 4;
                responseText = responseXML = text;
                responseJS = js;
            } else {
                status = 500;
                responseText = responseXML = responseJS = null;
            }
            _changeReadyState(2);
            _changeReadyState(3);
            _changeReadyState(4);
            _cleanupScript();
        }},

        // Called on error.
        _error: function(msg) {
            throw (window.Error? new Error(msg) : msg);
        },

        // Create new XMLHttpRequest object.
        _obtainXmlReq: function(id, url) {
            // If url.domain specified and differ from current, cannot use XMLHttpRequest!
            // XMLHttpRequest (and MS ActiveX'es) cannot work with different domains.
            var p = url.match(new RegExp('^[a-z]+://(.*)', 'i'));
            if (p) {
                var curHost = document.location.host.toLowerCase();
                if (p[1].substring(0, curHost.length).toLowerCase() == curHost) {
                    url = p[1].substring(curHost.length, p[1].length);
                } else {
                    return null;
                }
            }
            
            // Try to use built-in loaders.
            var req = null;
            if (window.XMLHttpRequest) {
                try { req = new XMLHttpRequest() } catch(e) {}
            } else if (window.ActiveXObject) {
                try { req = new ActiveXObject("Microsoft.XMLHTTP") } catch(e) {}
                if (!req) try { req = new ActiveXObject("Msxml2.XMLHTTP") } catch (e) {}
            }
            if (req) {
                var th = this;
                req.onreadystatechange = function() { 
                    if (req.readyState == 4) {
                        // Avoid memory leak by removing closure.
                        req.onreadystatechange = th.dummy;
                        th.status = null;
                        try { 
                            // In case of abort() call, req.status is unavailable and generates exception.
                            // But req.readyState equals to 4 in this case. Stupid behaviour. :-(
                            th.status = req.status;
                            th.responseText = req.responseText;
                        } catch (e) {}
                        if (!th.status) return;
                        var funcRequestBody = null;
                        try {
                            // Prepare generator function & catch syntax errors on this stage.
                            eval('funcRequestBody = function() {\n' + th.responseText + '\n}');
                        } catch (e) {
                            return th._error("JavaScript code generated by backend is invalid!\n" + th.responseText)
                        }
                        // Call associated dataReady() outside try-catch block 
                        // to pass excaptions in onreadystatechange in usual manner.
                        funcRequestBody();
                    }
                };
                this._id = id;
            }
            return req;
        },

        // Create new script element and start loading.
        _obtainScript: function(id, href) { with (document) {
            // Oh shit! Damned stupid fucked Opera 7.23 does not allow to create SCRIPT 
            // element over createElement (in HEAD or BODY section or in nested SPAN - 
            // no matter): it is created deadly, and does not respons on href assignment.
            // So - always create SPAN.
            var span = createElement('SPAN');
            span.style.display = 'none';
            body.insertBefore(span, body.lastChild);
            span.innerHTML = 'Text for stupid IE.<s'+'cript></' + 'script>';
            setTimeout(function() {
                var s = span.getElementsByTagName('script')[0];
                s.language = 'JavaScript';
                if (s.setAttribute) s.setAttribute('src', href); else s.src = href;
            }, 10);
            this._id = id;
            this._span = span;
        }},

        // Create & submit form.
        _obtainForm: function(id, url, method, queryText, queryElem) {
            // In case of GET method - split real query string.
            if (method == 'GET') {
                queryText = url.split('?', 2)[1].split('&');
                url = url.split('?', 2)[0];
            }

            // Create invisible IFRAME with temporary form (form is used on empty queryElem).
            var div = document.createElement('DIV');
            div.id = 'jshr_d_' + id;
            div.style.position = 'absolute';
            div.style.visibility = 'hidden';
            div.innerHTML = 
                '<form enctype="multipart/form-data"></form>' + // stupid IE, MUST use innerHTML assignment :-(
                '<iframe src="javascript:\'\'" name="jshr_i_' + id + '" style="width:0px; height:0px; overflow:hidden; border:none"></iframe>';
            var form = div.getElementsByTagName('FORM')[0];
            var iframe = div.getElementsByTagName('IFRAME')[0];

            // Check if all form elements belong to same form.
            if (queryElem.length) {
                // If we have at least one form element, we use its form as POST container.
                form = queryElem[0][1].form;
                var foundFile = false;
                for (var i = 0; i < queryElem.length; i++) {
                    var e = queryElem[i][1];
                    if (!e.form) {
                        return this._error('Element "' + e.name + '" do not belongs to any form!');
                    }
                    if (e.form != form) {
                        return this._error('Element "' + e.name + '" belongs to different form. All elements must belong to the same form!');
                    }
                    foundFile = foundFile || (e.tagName.toLowerCase() == 'input' && (e.type||'').toLowerCase() == 'file');
                }
                var et = "multipart/form-data";
                if (form.enctype != et && foundFile) {
                    return this._error('Attribute "enctype" of elements\' form must be "' + et + '" (for IE), "' + form.enctype + '" given.');
                }
            }

            // Temporary disable ALL form elements in 'form' (including custom!).
            for (var i = 0; i < form.elements.length; i++) {
                var e = form.elements[i];
                if (e.name != null) {
                    e.jshrSaveName = e.name;
                    e.name = '';
                }
            }

            // Insert hidden fields to the form.
            var tmpE = [];
            for (var i=0; i<queryText.length; i++) {
                var pair = queryText[i].split('=', 2);
                var e = document.createElement('INPUT');
                e.type = 'hidden';
                e.name = unescape(pair[0]);
                e.value = pair[1] != null? unescape(pair[1]) : '';
                form.appendChild(e);
                tmpE[tmpE.length] = e;
            }

            // Enable custom form elements back & change their names.
            for (var i = 0; i < queryElem.length; i++) queryElem[i][1].name = queryElem[i][0];

            // Insert generated form inside the document.
            // Be careful: don't forget to close FORM container in document body!
            document.body.insertBefore(div, document.body.lastChild);
            this._span = div;

            // Temporary modify form attributes, submit form, restore attributes back.
            var sv = {};
            sv.enctype  = form.enctype;  form.enctype = "multipart/form-data";
            sv.action   = form.action;   form.action = url;
            sv.method   = form.method;   form.method = method;
            sv.target   = form.target;   form.target = iframe.name;
            sv.onsubmit = form.onsubmit; form.onsubmit = null;
            form.submit();
            for (var i in sv) form[i] = sv[i];
            
            // Remove generated temporary hidden elements from form.
            for (var i = 0; i < tmpE.length; i++) tmpE[i].parentNode.removeChild(tmpE[i]);

            // Enable all disabled elements back.
            for (var i = 0; i < form.elements.length; i++) {
                var e = form.elements[i];
                if (e.jshrSaveName != null) {
                    e.name = e.jshrSaveName;
                    e.jshrSaveName = null;
                }
            }
        },

        // Remove last used script element (clean memory).
        _cleanupScript: function() {
            var span = this._span;
            if (span) {
                this._span = null;
                setTimeout(function() {
                    // without setTimeout - crash in IE 5.0!
                    span.parentNode.removeChild(span);
                }, 50);
            }
            if (this._id) {
                // Mark this loading as aborted.
                PENDING[this._id] = false;
            }
            return false;
        },

        // Convert hash to QUERY_STRING.
        // If next value is scalar or hash, push it to queryText.
        // If next value is form element, push [name, element] to queryElem.
        _hash2query: function(content, prefix, queryText, queryElem) {
            if (prefix == null) prefix = "";
            if (content instanceof Object) {
                for (var k in content) {
                    var v = content[k];
                    if (v instanceof Function) continue;
                    var curPrefix = prefix? prefix+'['+this.escape(k)+']' : this.escape(k);
                    if (this._isFormElement(v)) {
                        var tn = v.tagName.toLowerCase();
                        if (tn == 'form') {
                            // This is FORM itself. Add all its elements.
                            for (var i=0; i<v.elements.length; i++) {
                                var e = v.elements[i];
                                if (e.name) queryElem[queryElem.length] = [e.name, e];
                            }
                        } else if (tn == 'input' || tn == 'textarea' || tn == 'select') {
                            // This is a single form elemenent.
                            queryElem[queryElem.length] = [curPrefix, v];
                        } else {
                            return this._error('Invalid FORM element detected: name=' + (e.name||'') + ', tag=' + e.tagName);
                        }
                    } else if (v instanceof Object) {
                        this._hash2query(v, curPrefix, queryText, queryElem);
                    } else {
                        // We MUST skip NULL values, because there is no method
                        // to pass NULL's via GET or POST request in PHP.
                        if (v === null) continue;
                        queryText[queryText.length] = curPrefix + "=" + this.escape('' + v);
                    }
                }
            } else {
                queryText = [content];
            }
            return true;
        },

        // Return true if e is any form element of FORM itself.
        _isFormElement: function(e) {
            // Fast & dirty method.
            return e && e.ownerDocument && e.parentNode && e.parentNode.appendChild && e.tagName;
        },

        // Return value of SID based on QUERY_STRING or cookie
        // (PHP compatible sessions).
        _getSid: function() {
            var m = document.location.search.match(new RegExp('[&?]'+this.session_name+'=([^&?]*)'));
            var sid = null;
            if (m) {
                sid = m[1];
            } else {
                var m = document.cookie.match(new RegExp('(;|^)\\s*'+this.session_name+'=([^;]*)'));
                if (m) sid = m[2];
            }
            return sid;
        },

        // Change current readyState and call trigger method.
        _changeReadyState: function(s, reset) { with (this) {
            if (reset) {
                status = statusText = responseJS = null;
                responseText = '';
            }
            readyState = s;
            if (onreadystatechange) onreadystatechange();
        }},

        // Stupid JS escape() does not quote '+'.
        escape: function(s) {
            return escape(s).replace(new RegExp('\\+','g'), '%2B');
        }
    }
})();
