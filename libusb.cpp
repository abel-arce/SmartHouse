#include <iostream>
#include <libusb-1.0/libusb.h>

//g++ -g -Wall -L/usr/local/lib/ libusb.cpp -o USB -lusb-1.0

using namespace std;

void printdev(libusb_device *dev);

int main(){	
	
	libusb_device_handle *dev_handle;
	libusb_device **devs;
	libusb_context *ctx = NULL;
	int r;
	
	ssize_t cnt;
	r = libusb_init(&ctx);
	
	if(r < 0){
		cout<<"Init Error"<<endl;
		return 1;	
	}
		
	libusb_set_debug(ctx, 3);
	cnt = libusb_get_device_list(ctx, &devs);

	if(cnt < 0){
        	cout<<"Get Device Error"<<endl;
    	}

	/*ssize_t i;
	
	for(i = 0; i < cnt; i++) {
                printdev(devs[i]); //print specs of this device
        }
        */
	cout<<"Establishing the Bulk comunication"<<endl;
	
	dev_handle = libusb_open_device_with_vid_pid(ctx, 1240, 11);
	
	
	if(dev_handle == NULL)
        cout<<"Cannot open device"<<endl;
    else
        cout<<"Device Opened"<<endl;

	libusb_free_device_list(devs, 1);
	unsigned char *data = new unsigned char[4];	
	data[0]=0x7f;	
	int actual;
	

	if(libusb_kernel_driver_active(dev_handle, 0) == 1) { //find out if kernel driver is attached

        cout<<"Kernel Driver Active"<<endl;

        if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
            cout<<"Kernel Driver Detached!"<<endl;

    }
	
	r = libusb_claim_interface(dev_handle, 0);
	
	if(r < 0) {
        cout<<"Cannot Claim Interface"<<endl;
        return 1;
    }

	cout<<"Claimed Interface"<<endl;

	cout<<"Data->"<<data<<"<-"<<endl; //just to see the data we want to write : abcd

    cout<<"Writing Data..."<<endl;

    for(int it=0;it<4;it++){
    	r = libusb_bulk_transfer(dev_handle, 1, data, 1, &actual, 0);
    	
    	if(r == 0 && actual == 1)
    		cout<<"Writing Successful!"<<endl;
        else
            cout<<"Write Error actual:"<<actual<<endl;
    }

	r = libusb_release_interface(dev_handle, 0); //release the claimed interface

    if(r!=0) {
        cout<<"Cannot Release Interface"<<endl;
        return 1;
    }

    cout<<"Released Interface"<<endl;


    libusb_close(dev_handle); //free the device that was opened.
    libusb_exit(ctx); //close the session
	
	

        return 0;

}

void printdev(libusb_device *dev) {
   
    libusb_device_descriptor desc;
    
    int r = libusb_get_device_descriptor(dev, &desc);
    
    if (r < 0) {
        cout<<"failed to get device descriptor"<<endl;
        return;
    }
	cout<<"Number of possible configurations: "<<(int)desc.bNumConfigurations<<"  ";

    cout<<"Device Class: "<<(int)desc.bDeviceClass<<"  ";

    cout<<"VendorID: "<<desc.idVendor<<"  ";

    cout<<"ProductID: "<<desc.idProduct<<endl;

    libusb_config_descriptor *config;

    libusb_get_config_descriptor(dev, 0, &config);

    cout<<"Interfaces: "<<(int)config->bNumInterfaces<<" ||| ";

    const libusb_interface *inter;

    const libusb_interface_descriptor *interdesc;

    const libusb_endpoint_descriptor *epdesc;

    for(int i=0; i<(int)config->bNumInterfaces; i++) {

        inter = &config->interface[i];

        cout<<"Number of alternate settings: "<<inter->num_altsetting<<" | ";

        for(int j=0; j<inter->num_altsetting; j++) {

            interdesc = &inter->altsetting[j];

            cout<<"Interface Number: "<<(int)interdesc->bInterfaceNumber<<" | ";

            cout<<"Number of endpoints: "<<(int)interdesc->bNumEndpoints<<" | ";

            for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {

                epdesc = &interdesc->endpoint[k];

                cout<<"Descriptor Type: "<<(int)epdesc->bDescriptorType<<" | ";

                cout<<"EP Address: "<<(int)epdesc->bEndpointAddress<<" | ";

            }

        }

    }

    cout<<endl<<endl<<endl;

    libusb_free_config_descriptor(config);

}


