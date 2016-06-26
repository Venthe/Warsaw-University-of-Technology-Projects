package lab3Project;

public enum Method {
		CENTER,
		ENLARGE,
		SHRINK,
		CUTOUT;
		public static Method returnMethodFromString(String input){
			Method result = null;
			if(input.toLowerCase().equals("center")||input.toLowerCase().equals("center images")){
				result = Method.CENTER;
			}
			else if(input.toLowerCase().equals("enlarge")||input.toLowerCase().equals("resize (enlarge)")){
				result = Method.ENLARGE;
			}
			else if(input.toLowerCase().equals("shrink")||input.toLowerCase().equals("resize (shrink)")){
				result = Method.SHRINK;
			}
			else if(input.toLowerCase().equals("cutout")||input.toLowerCase().equals("cut out")){
				result = Method.CUTOUT;
			}
			return result;
		}
}
