function externalLinks()
{
  d = document.getElementsByTagName('form');
  for(var i = 0; i < d.length; i++)
  {
    var form = d[i];
    var t = form.getAttribute('action');
    if(t && t[0] == ';')
    {
      form.target = '_blank';
      form.action = t.substr(1);
    }
  }
}
window.onload = externalLinks;
