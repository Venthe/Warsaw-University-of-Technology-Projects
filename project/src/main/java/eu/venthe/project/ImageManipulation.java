package eu.venthe.project;

import com.sun.media.jai.codec.FileSeekableStream;
import com.sun.media.jai.codec.TIFFDecodeParam;
import eu.venthe.project.model.ImageCombinationMethod;
import eu.venthe.project.model.ImageExtension;
import eu.venthe.project.model.ImageManipulationMethod;
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


public class ImageManipulation {

  // saving
  // User selects a format and the properties he likes.
  // Available options: .bmp, .png, .jpg, .jpeg, .tiff, .tif.
  // Available depths: 1 bpp, 8 bpp, 16 bpp, 24bp p, 32bpp .
  // You do not use compression for saving the results.
  // Note that if we save grayscale image in 1bpp precision we get black/white image.

  private static int returnMinimumCachedImagesSize(ArrayList<ArrayList<BufferedImage>> images) {
    int result = 0;
    for (int i = 0; i < images.size(); i++) {
      if (images.get(i).size() > 0) {
        if (result == 0 || result > images.get(i).size()) {
          result = images.get(i).size();
        }
      }
    }
    return result;
  }

  public static BufferedImage bufferedImageFromImageIcon(ImageIcon ico) {
    BufferedImage bi = new BufferedImage(
        ico.getIconWidth(),
        ico.getIconHeight(),
        BufferedImage.TYPE_INT_RGB);
    Graphics g = bi.createGraphics();
    // paint the Icon to the BufferedImage.
    ico.paintIcon(null, g, 0, 0);
    g.dispose();
    return bi;
  }

  public static ArrayList<BufferedImage> mergeDirectories(
      ArrayList<ArrayList<BufferedImage>> images, ImageCombinationMethod imageCombinationMethod, ImageManipulationMethod imageManipulationMethod) {
    ArrayList<BufferedImage> result = new ArrayList<>(); // End result - array of merged images
    int numberOfFilesToMerge = returnMinimumCachedImagesSize(images);

    System.out.println(
        "Merging directories using imageCombinationMethod " + imageCombinationMethod.toString() + " and imageManipulationMethod " + imageManipulationMethod
            .toString()
            + ". First " + numberOfFilesToMerge
            + " images from eglible directories will be merged");
    ArrayList<ArrayList<BufferedImage>> imagesBuffer = new ArrayList<>();

    System.out.println("Transposing Images matrix");

    //TODO: If only 1 common image, then ceate an array out of it
    for (int i = 0; i < numberOfFilesToMerge; i++) {
      imagesBuffer.add(new ArrayList<>());
      for (int j = 0; j < images.size(); j++) {
        if (images.get(j).size() > 1) {
          imagesBuffer.get(i).add(images.get(j).get(i));
        }
      }
    }

    for (int i = 0; i < imagesBuffer.size(); i++) {
      result.add(mergeArrayOfImages(imagesBuffer.get(i), imageCombinationMethod, imageManipulationMethod));
    }
    return result;
  }

  private static BufferedImage mergeArrayOfImages(ArrayList<BufferedImage> images, ImageCombinationMethod imageCombinationMethod,
      ImageManipulationMethod imageManipulationMethod) {
    // from images start to end merge i and i+1
    BufferedImage result = images.get(0);
    if (images.size() > 1) {
      for (int i = 1; i < images.size(); i++) {
        result = mergeImage(result, images.get(i), imageCombinationMethod, imageManipulationMethod);
      }
    }
    return result;
  }


  private static BufferedImage mergeImage(BufferedImage a, BufferedImage b, ImageCombinationMethod imageCombinationMethod,
      ImageManipulationMethod imageManipulationMethod) {
    //TODO: Only 8bit?
    //TODO: No imageManipulationMethod center and cutout
    System.out.println(
        "Merging " + a.hashCode() + " with " + b.hashCode() + " using " + imageCombinationMethod.toString() + ", "
            + imageManipulationMethod.toString());
    BufferedImage result = null;
    if (imageManipulationMethod.equals(ImageManipulationMethod.CENTER)) {
      result = a;

    } else if (imageManipulationMethod.equals(ImageManipulationMethod.ENLARGE) || imageManipulationMethod
        .equals(ImageManipulationMethod.SHRINK)) {
      if (imageManipulationMethod.equals(ImageManipulationMethod.ENLARGE)) {
        if ((a.getHeight() * a.getWidth()) > (b.getWidth() * b.getHeight())) {
          b = resizeImage(b, a.getWidth(), a.getHeight());
        } else {
          a = resizeImage(a, b.getWidth(), b.getHeight());
        }
      } else if (imageManipulationMethod.equals(ImageManipulationMethod.SHRINK)) {
        if ((a.getHeight() * a.getWidth()) < (b.getWidth() * b.getHeight())) {
          b = resizeImage(b, a.getWidth(), a.getHeight());
        } else {
          a = resizeImage(a, b.getWidth(), b.getHeight());
        }
      }

      result = new BufferedImage(a.getWidth(), a.getHeight(), BufferedImage.TYPE_INT_ARGB);
      for (int y = a.getHeight() - 1; y >= 0; y--) {
        for (int x = a.getWidth() - 1; x >= 0; x--) {
          int merged = mergePixel(new Color(a.getRGB(x, y)).getRed(),
              new Color(b.getRGB(x, y)).getRed(), imageCombinationMethod);
          result.setRGB(x, y, new Color(merged, merged, merged).getRGB());
        }
      }
    } else if (imageManipulationMethod.equals(ImageManipulationMethod.CUTOUT)) {
      result = a;

    } //TODO:
    else {
      throw new IllegalArgumentException("ImageManipulationMethod must be " + ImageManipulationMethod.values());
    }
    return result;
  }

  private static int mergePixel(int pixel1, int pixel2, ImageCombinationMethod imageCombinationMethod) {
    int result = -1;
    try {
      if (imageCombinationMethod.equals(ImageCombinationMethod.AND)) {
        result = (pixel1 <= pixel2) ? pixel1 : pixel2;
      } else if (imageCombinationMethod.equals(ImageCombinationMethod.OR)) {
        result = (pixel1 > pixel2) ? pixel1 : pixel2;
      } else if (imageCombinationMethod.equals(ImageCombinationMethod.XOR)) {
        result = pixel1 - pixel2;
        result = (result < 0) ? result * -1 : result;
      } else {
        throw new IllegalArgumentException("imageCombinationMethod must be " + ImageCombinationMethod.values());
      }
    } catch (Throwable e) {
      e.printStackTrace();
    }
    return result;
  }

  public static BufferedImage resizeImage(BufferedImage img, int width, int height) {
    Image tmp = img.getScaledInstance(width, height, Image.SCALE_SMOOTH);
    BufferedImage dimg = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);

    Graphics2D g2d = dimg.createGraphics();
    g2d.drawImage(tmp, 0, 0, null);
    g2d.dispose();

    return dimg;
  }

  public static Image loadImageAsImage(String path) {
    // TODO: Various bit sized images are loaded as 8bit
    Image img = null;
    try {
      if (path.endsWith(".tif") || path.endsWith(".tiff")) {
        FileSeekableStream stream = new FileSeekableStream(path);
        TIFFDecodeParam decodeParam = new TIFFDecodeParam();
        decodeParam.setDecodePaletteAsShorts(true);
        ParameterBlock params = new ParameterBlock();
        params.add(stream);
        RenderedOp image1 = JAI.create("tiff", params);
        img = image1.getAsBufferedImage();
      } else {
        img = ImageIO.read(new File(path));
      }
    } catch (IOException e) {
      System.out.println(path);
      e.printStackTrace();
    }
    System.out.println("Image loaded: " + path);

    return img;
  }

  public static void saveArrayOfImages(ArrayList<BufferedImage> img, String path, ImageExtension ext) {
    for (int i = 0; i < img.size(); i++) {
      saveImage(img.get(i), path + "_" + i, ext);
    }
  }

  private static void saveImage(BufferedImage img, String filename, ImageExtension ext) {
    System.out.println("Saving " + filename + "." + ext.toString().toLowerCase());
    //TODO: other formats than PNG
    if (ext.equals(ImageExtension.PNG)) {
      File outputfile = new File(filename + "." + "png");
      try {
        ImageIO.write(img, "png", outputfile);
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
  }
}
