package lab3Project;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.image.renderable.ParameterBlock;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.media.jai.JAI;
import javax.media.jai.RenderedOp;
import javax.swing.ImageIcon;

import com.sun.media.jai.codec.FileSeekableStream;
import com.sun.media.jai.codec.TIFFDecodeParam;


public class ImageManipulation{

	// saving
	// User selects a format and the properties he likes. 
	// Available options: .bmp, .png, .jpg, .jpeg, .tiff, .tif.
	// Available depths: 1 bpp, 8 bpp, 16 bpp, 24bp p, 32bpp .
	// You do not use compression for saving the results. 
	// Note that if we save grayscale image in 1bpp precision we get black/white image. 
	
	private static int returnMinimumCachedImagesSize(ArrayList<ArrayList<BufferedImage>> images){
		int result = 0;
		for(int i=0;i<images.size();i++){
			if(images.get(i).size()>0){
				if(result==0||result>images.get(i).size()){
					result = images.get(i).size();
				}
			}
		}
		return result;
	}
	public static BufferedImage bufferedImageFromImageIcon(ImageIcon ico){
		BufferedImage bi = new BufferedImage(
				ico.getIconWidth(),
				ico.getIconHeight(),
			    BufferedImage.TYPE_INT_RGB);
			Graphics g = bi.createGraphics();
			// paint the Icon to the BufferedImage.
			ico.paintIcon(null, g, 0,0);
			g.dispose();
		return bi;
	}
	public static ArrayList<BufferedImage> mergeDirectories(ArrayList<ArrayList<BufferedImage>> images, Type type, Method method)
	{
		ArrayList<BufferedImage> result = new ArrayList<BufferedImage>(); // End result - array of merged images
		int numberOfFilesToMerge = returnMinimumCachedImagesSize(images);
		
		System.out.println("Merging directories using type "+type.toString()+" and method "+method.toString()+". First "+numberOfFilesToMerge+" images from eglible directories will be merged");
		ArrayList<ArrayList<BufferedImage>> imagesBuffer = new ArrayList<ArrayList<BufferedImage>>();

		System.out.println("Transposing Images matrix");
		
		//TODO: If only 1 common image, then ceate an array out of it
		for(int i=0;i<numberOfFilesToMerge;i++){
			imagesBuffer.add(new ArrayList<BufferedImage>());
			for(int j =0;j<images.size();j++){
				if(images.get(j).size()>1){
					imagesBuffer.get(i).add(images.get(j).get(i));
				}
			}
		}

		
		
		
		for(int i=0;i<imagesBuffer.size();i++){
			result.add(mergeArrayOfImages(imagesBuffer.get(i), type, method));
		}
		return result;
	}
	private static BufferedImage mergeArrayOfImages(ArrayList<BufferedImage> images, Type type, Method method){
		// from images start to end merge i and i+1
		BufferedImage result=images.get(0);
		if(images.size()>1){
			for(int i=1;i<images.size();i++){
				result = mergeImage(result,images.get(i),type,method);
			}
		}
		return result;
	}
	

	private static BufferedImage mergeImage(BufferedImage a, BufferedImage b, Type type, Method method){
		//TODO: Only 8bit?
		//TODO: No method center and cutout
		//saveImage(a, System.getProperty("user.home") + "\\Desktop\\"+"merge_a"+a.hashCode(), Extension.PNG);
		//saveImage(b, System.getProperty("user.home") + "\\Desktop\\"+"merge_b"+b.hashCode(), Extension.PNG);
		System.out.println("Merging "+a.hashCode()+" with "+b.hashCode()+" using "+type.toString()+", "+method.toString());
		BufferedImage result = null;
		if(method.equals(Method.CENTER)){
			result = a;
			
		}
		else if (method.equals(Method.ENLARGE)||method.equals(Method.SHRINK)){
			if(method.equals(Method.ENLARGE)){
				if((a.getHeight()*a.getWidth())>(b.getWidth()*b.getHeight())){
					b = resizeImage(b, a.getWidth(), a.getHeight());
				}
				else {
					a = resizeImage(a,b.getWidth(),b.getHeight());
				}
			}
			else if(method.equals(Method.SHRINK)){
				if((a.getHeight()*a.getWidth())<(b.getWidth()*b.getHeight())){
					b = resizeImage(b, a.getWidth(), a.getHeight());
				}
				else {
					a = resizeImage(a,b.getWidth(),b.getHeight());
				}
			}

			result = new BufferedImage(a.getWidth(),a.getHeight(), BufferedImage.TYPE_INT_ARGB);
		    for(int y=a.getHeight()-1;y>=0;y--){
			    for(int x=a.getWidth()-1;x>=0;x--){
			    	int merged = mergePixel(new Color(a.getRGB(x, y)).getRed(),new Color(b.getRGB(x, y)).getRed(),type);
			    	result.setRGB(x, y, new Color(merged,merged,merged).getRGB());
		    	}
		    }
		}
		else if(method.equals(Method.CUTOUT)){
			result = a;
			
		} //TODO: 
		else {
			throw new IllegalArgumentException("Method must be "+Method.values());
		}
		//saveImage(result, System.getProperty("user.home") + "\\Desktop\\"+"merge_result"+result.hashCode(), Extension.PNG);
		return result;
	}
	
	private static int mergePixel(int pixel1,int pixel2, Type type){
		int result=-1;
		try{
			if(type.equals(Type.AND)){
				result = (pixel1<=pixel2) ? pixel1 : pixel2;
			}
			else if (type.equals(Type.OR)){
				result = (pixel1>pixel2) ? pixel1 : pixel2;
				}
			else if (type.equals(Type.XOR)){
				result = pixel1-pixel2;
				result = (result<0) ? result*-1 : result;
				}
			else {
				throw new IllegalArgumentException("type must be "+Type.values());
			}
		}
		catch (Throwable e){
			e.printStackTrace();
		}
		return result;
	}
	public static BufferedImage resizeImage(BufferedImage img, int width,int height){
	    Image tmp = img.getScaledInstance(width, height, Image.SCALE_SMOOTH);
	    BufferedImage dimg = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);

	    Graphics2D g2d = dimg.createGraphics();
	    g2d.drawImage(tmp, 0, 0, null);
	    g2d.dispose();
	    
	    return dimg;
	}
	public static Image loadImageAsImage(String path){
		// TODO: Various bit sized images are loaded as 8bit
		Image img = null;
		try {
			if(path.endsWith(".tif")||path.endsWith(".tiff")){
				FileSeekableStream stream = new FileSeekableStream(path);
				TIFFDecodeParam decodeParam = new TIFFDecodeParam();
				decodeParam.setDecodePaletteAsShorts(true);
				ParameterBlock params = new ParameterBlock();
				params.add(stream);
				RenderedOp image1 = JAI.create("tiff", params);
				img = (BufferedImage) image1.getAsBufferedImage();
			}
			else{
				img = ImageIO.read(new File(path));
			}
		} catch (IOException e) {
			System.out.println(path);
			e.printStackTrace();
		}
		System.out.println("Image loaded: "+path);
		
		return img;
	}

	public static void saveArrayOfImages(ArrayList<BufferedImage> img,String path, Extension ext){
		for(int i =0;i<img.size();i++){
			saveImage(img.get(i),path+"_"+i,ext);
		}
	}
	private static void saveImage(BufferedImage img, String filename, Extension ext){
		System.out.println("Saving "+filename+"."+ext.toString().toLowerCase());
		//TODO: other formats than PNG
		if(ext.equals(Extension.PNG)){
			File outputfile = new File(filename+"."+"png");
			try {
				ImageIO.write(img, "png", outputfile);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	// Internal test function
	@SuppressWarnings("unused")
	private static void printColorDataBW(BufferedImage dimg){
	    for(int y=dimg.getHeight()-1;y>=0;y--){
	    	System.out.print("[ ");
		    for(int x=dimg.getWidth()-1;x>=0;x--){
		    	Color c = new Color(dimg.getRGB(x, y));
		    	if(c.getRed()<10){System.out.print("00");}
		    	else if(c.getRed()<100){System.out.print("0");}
		    	System.out.print(c.getRed()+" ");
	    	}
	    	System.out.println("]");
	    }
	}
	
}
