package lab3Project;

public enum Type {
	AND,
	OR,
	XOR;
	public static Type returnTypeFromString(String input){
		Type result = null;
		if(input.toLowerCase().equals("and")){
			result = Type.AND;
		}
		else if(input.toLowerCase().equals("or")){
			result = Type.OR;
		}
		else if(input.toLowerCase().equals("xor")){
			result = Type.XOR;
		}
		return result;
	}
}
