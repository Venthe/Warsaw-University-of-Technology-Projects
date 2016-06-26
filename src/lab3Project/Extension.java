package lab3Project;

public enum Extension {
	JPG,
	PNG,
	TIF,
	BMP;
	public static Extension returnExtensionFromString(String input){
		Extension result = null;
		if(input.toLowerCase().equals("jpg")||input.toLowerCase().equals("jpeg")){
			result = Extension.JPG;
		}
		else if(input.toLowerCase().equals("png")){
			result = Extension.PNG;
		}
		else if(input.toLowerCase().equals("tif")||input.toLowerCase().equals("tiff")){
			result = Extension.TIF;
		}
		else if(input.toLowerCase().equals("bmp")){
			result = Extension.BMP;
		}
		return result;
	}
}
