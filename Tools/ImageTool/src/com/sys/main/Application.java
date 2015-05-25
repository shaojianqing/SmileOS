package com.sys.main;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Application {

	private final static String CREATE_IMAGE = "createImage";
	
	private final static String COPY_BINARY = "copyBinary";
	
	private final static String CONVERT_IMAGE = "convertImage";
	
	private final static String BUILD_CHARSET = "buildCharSet";
	
	private final static String TRIM_ELF_HEADER = "trimElfHeader";
	
	private final static String FILL_BYTE_CONTENT = "fillByteContent";
	
	private final static int BMP_HEADER_OFFSET = 54;
	
	private final static int IMG_HEADER_OFFSET = 8;
	
	private final static int SECTOR_BYTE_SIZE = 512;
	
	private final static int ELF_HEADER_OFFSET = 0x400;
	
	private static FileOutputStream fileOutput;
	
	private static FileInputStream sourceInput;
	
	private static FileInputStream targetInput;
	
	public static void main(String args[]) {
		try {			
			if (args != null && args.length > 0) {
				String command = args[0];
				String currentDir = System.getProperty("user.dir");
				if (CREATE_IMAGE.equals(command)) {
					createImage(args, currentDir);
				} else if (COPY_BINARY.equals(command)) {
					copyBinary(args, currentDir);
				} else if (CONVERT_IMAGE.equals(command)) {
					convertImage(args, currentDir);
				} else if (BUILD_CHARSET.equals(command)) {
					buildCharset(args, currentDir);
				} else if (TRIM_ELF_HEADER.equals(command)) {
					trimElfHeader(args, currentDir);
				} else if (FILL_BYTE_CONTENT.equals(command)) {
					fillByteContent(args, currentDir);
				}
			} else {
				System.out.println("Error: No Input Parameter   ssss   !");
			}
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Error: Parameter Is Invalid----->main!");
		}
	}

	private static void copyBinary(String[] args, String currentDir) throws FileNotFoundException, IOException {
		if (args.length == 4) {
			String source = args[1];
			String target = args[2];
			String positionStr = args[3];
			int position = Integer.valueOf(positionStr);
			sourceInput = new FileInputStream(new File(currentDir, source));
			targetInput = new FileInputStream(new File(currentDir, target));
			
			int sourceSize = sourceInput.available();
			int targetSize = targetInput.available();
			
			byte sourceData[] = new byte[sourceSize];
			byte targetData[] = new byte[targetSize];
			
			sourceInput.read(sourceData);
			targetInput.read(targetData);
			
			if (targetSize + position < sourceSize) {
				for (int i=0; i<targetSize; ++i) {
					sourceData[i + position] = targetData[i];
				}
				fileOutput = new FileOutputStream(new File(currentDir, source));
				fileOutput.write(sourceData);
				
				sourceInput.close();
				targetInput.close();
				fileOutput.close();
			} else {
				System.out.println("Error: Target File Size Or Position Is INCORRECT!");
			}						
		} else {
			System.out.println("Error: Parameters Is Invalid----->copyBinary!");
		}
	}

	private static void createImage(String[] args, String currentDir) throws IOException, FileNotFoundException {
		if (args.length == 3) { 
			String name = args[1];
			String sizeStr = args[2];
			int size = Integer.valueOf(sizeStr);
			byte data[] = new byte[size];
			File file = new File(currentDir, name);
			if (!file.exists()) {
				if (file.createNewFile()) {
					fileOutput = new FileOutputStream(file);
					fileOutput.write(data);
					
					fileOutput.close();
				} else {
					System.out.println("Error: Fail to create File!");
				}
			} else {
				System.out.println("Error: File has existed!");
			}
		} else {
			System.out.println("Error: Parameters Is Invalid----->createImage!");
		}
	}
	
	private static void convertImage(String[] args, String currentDir) throws IOException, FileNotFoundException {
		if (args.length == 6) {
			String sourceBmp = args[1];
			String targetImg = args[2];
			String widthStr = args[3];
			String heightStr = args[4];
			String hasTransStr = args[5];
			int width = Integer.valueOf(widthStr);
			int height = Integer.valueOf(heightStr);
			boolean hasTrans  = Boolean.valueOf(hasTransStr);
			
			File sourceFile = new File(currentDir, sourceBmp);
			File targetFile = new File(currentDir, targetImg);
			if (sourceFile.exists() && !targetFile.exists() && targetFile.createNewFile()) {
				sourceInput = new FileInputStream(sourceFile);
				targetInput = new FileInputStream(targetFile);
				fileOutput = new FileOutputStream(targetFile);
				
				int sourceSize = sourceInput.available();
				int targetSize = width*height*3 + 8;
				byte[] sourceData = new byte[sourceSize];
				byte[] targetData = new byte[targetSize];
				
				sourceInput.read(sourceData);
				targetData[0] = 'I';
				targetData[1] = 'M';
				targetData[2] = 'A';
				targetData[3] = 'G';
				
				targetData[4] = (byte)(width&0xFF);
				targetData[5] = (byte)((width&0xFF00)/0x100);
				
				targetData[6] = (byte)(height&0xFF);
				targetData[7] = (byte)((height&0xFF00)/0x100);
				
				for (int i=0;i<sourceSize-BMP_HEADER_OFFSET;++i) {
					byte data = sourceData[i+BMP_HEADER_OFFSET];
					if (hasTrans && data == 0x00) {
						data = 0x01;
					}
					targetData[i+IMG_HEADER_OFFSET] = data;
				}
				fileOutput.write(targetData);
			} else {
				System.out.println("Source File not exists or Target File exists!");
			}
		} else {
			System.out.println("Error: Parameters Is Invalid!");
		}
	}
	
	private static void buildCharset(String[] args, String currentDir) throws IOException, FileNotFoundException {
		if (args.length == 3) {
			String source = args[1];
			String target = args[2];
			
			File sourceFile = new File(currentDir, source);
			File targetFile = new File(currentDir, target);
			if (sourceFile.exists() && !targetFile.exists() && targetFile.createNewFile()) {
				fileOutput = new FileOutputStream(targetFile);				
				BufferedReader reader = new BufferedReader(new FileReader(sourceFile));
				String charLine = null;
				List<Byte> dataList = new ArrayList<Byte>();
				while ((charLine = reader.readLine()) != null) {
					charLine = charLine.replace('.', '0').replace('*', '1');
					byte data = Short.valueOf(charLine, 2).byteValue();
					dataList.add(data);
				}
				byte[] byteArray = new byte[dataList.size()];
				for (int i=0;i<dataList.size();++i) {
					byteArray[i] = dataList.get(i);
				}
				fileOutput.write(byteArray);
			}			
		} else {
			System.out.println("Error: Parameters Is Invalid----->buildCharset!");
		}
	}
	
	private static void trimElfHeader(String[] args, String currentDir) throws IOException, FileNotFoundException {
		if (args.length == 3) {
			String source = args[1];
			String target = args[2];
			
			File sourceFile = new File(currentDir, source);
			File targetFile = new File(currentDir, target);
			if (sourceFile.exists() && !targetFile.exists() && targetFile.createNewFile()) {
				sourceInput = new FileInputStream(sourceFile);
				fileOutput = new FileOutputStream(targetFile);
				
				int sourceSize = sourceInput.available();
				int targetSize = sourceSize - ELF_HEADER_OFFSET;
				byte[] sourceData = new byte[sourceSize];
				byte[] targetData = new byte[targetSize];
				sourceInput.read(sourceData);
				for (int i=ELF_HEADER_OFFSET;i<sourceSize;++i) {
					targetData[i - ELF_HEADER_OFFSET] = sourceData[i];
				}
				fileOutput.write(targetData);
			}			
		} else {
			System.out.println("Error: Parameters Is Invalid----->trimElfHeader!");
		}
	}
	
	private static void fillByteContent(String[] args, String currentDir) throws IOException, FileNotFoundException {
		if (args.length == 4) {
			String source = args[1];
			String positionStr = args[2];
			String content = args[3];
			byte cont = Byte.valueOf(content);
			sourceInput = new FileInputStream(new File(currentDir, source));
			
			int sourceSize = sourceInput.available();
			int position = Integer.valueOf(positionStr);
			
			byte sourceData[] = new byte[sourceSize];
			
			sourceInput.read(sourceData);
			
			if (sourceSize>SECTOR_BYTE_SIZE+position) {
				for (int i=position; i<sourceSize-SECTOR_BYTE_SIZE; ++i) {
					sourceData[i] = cont;
				}
				fileOutput = new FileOutputStream(new File(currentDir, source));
				fileOutput.write(sourceData);
				
				sourceInput.close();
				fileOutput.close();
			} else {
				System.out.println("Error: Target File Size Or Position Is INCORRECT!");
			}						
		} else {
			System.out.println("Error: Parameters Is Invalid----->fillByteContent!");
		}
	}
}
