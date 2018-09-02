class Debug {

	private static boolean debug = false;

	public static void print(String str) {
		if(debug) {
			System.out.print(str);
		}
	}

}