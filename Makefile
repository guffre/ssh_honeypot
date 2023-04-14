# Modified Makefile to allow for building of the standalone module

nss_name = libnss_identity
pam_name = pam_logpassword

nss_src = $(nss_name).c
nss_obj = $(nss_name).o
nss_lib = $(nss_name).so.2

pam_src = $(pam_name).c
pam_obj = $(pam_name).o
pam_lib = $(pam_name).so

all: $(nss_name).so.2 $(pam_name).so

$(nss_obj):
	gcc -fPIC -c $(nss_src) -o $(nss_obj)

$(nss_lib): $(nss_obj)
	ld -x --shared -o $@ $(nss_obj)

$(pam_obj):
	gcc -c $(pam_src) -o $(pam_obj)

$(pam_lib): $(pam_obj)
	ld --shared -o $@ $(pam_obj)

clean:
	rm -f $(nss_obj) $(nss_lib) core *~
	rm -f $(pam_obj) $(pam_lib) core *~
