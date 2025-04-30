#include <LPC214X.H>

void delay(int a){
	int i,j;
	for(i=0; i<a; i++)
	for(j=0; j<a;j++);
}

int main(){
		int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
		int i,j;
		IO0DIR=0x0000ffff;
		
	while(1){
		for(i=0; i<10; i++){
			IOSET0=arr[i];		// 1st 7 Seg
			delay(100);
			
			for(j=0; j<10; j++){
			 IO0SET=arr[j]<<8;
				delay(199);
				IO0CLR=arr[j]<<8;
			}
						IO0CLR=arr[i];	
		}
	
	}
} 




//#include <LPC214X.H>

//void delay(int a){
//	int i,j;
//	for(i=0; i<a; i++)
//	for(j=0; j<a;j++);
//}

//void main(){
//		int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
//		//int arr1[]={0x3f00,0x0600,0x5b00,0x4f00,0x6600,0x6d00,0x7d00,0x0700,0x7f00,0x6700};
//		int i,j;
//		IO0DIR=0xffffffff;
//		
//	while(1){
//		for(i=0; i<10 ; i++){
//			IOSET0=arr[i];
//			delay(100);
//			for(j=0; j<10; j++){
//			 IO0SET=arr1[j]<<8;
//				delay(199);
//				IO0CLR=arr1[j]<<8;
//			}
//						IO0CLR=arr[i];
//		}
//	
//	}
//}

		
