#include<Rs232Service.h>

static inline int* prepareRs232Service() {

	int* service_descriptor = startRs232Service();
	initRs232Service(service_descriptor);

	return service_descriptor;
}

static inline void dispatchRs232Services(int* service_descriptor) {

	pthread_create(&handshakeTx_service, NULL, &handshakeDeviceDriver, service_descriptor);
	pthread_create(&handshakeRx_service, NULL, &logHandshakingSignals, service_descriptor);

	pthread_join(handshakeRx_service, NULL);
}

int main(int argc, char **argv) {
	printf("%s\n", " --- Started Rs232 driver example --- ");
	
	dispatchRs232Services(prepareRs232Service());

	return 0;
}
