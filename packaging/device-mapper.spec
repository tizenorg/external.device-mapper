%define device_mapper_version 1.02.28
%define lvm2_version 2.02.79

# Do not reset Release to 1 unless both lvm2 and device-mapper 
# versions are increased together.

Name: device-mapper
Summary: Device mapper utility
Version: %{device_mapper_version}
Release: 1
License: GPLv2
Source0: ftp://sources.redhat.com/pub/lvm2/LVM2.%{lvm2_version}.tgz
Group: System/Base
URL: http://sources.redhat.com/dm
Requires: device-mapper-libs = %{device_mapper_version}-%{release}

%description -n device-mapper
This package contains the supporting userspace utility, dmsetup,
for the kernel device-mapper.

%package -n device-mapper-devel
Summary: Development libraries and headers for device-mapper
Version: %{device_mapper_version}
Release: %{release}
License: LGPLv2.1
Group: Development/Libraries
Requires: device-mapper = %{device_mapper_version}-%{release}
Requires: device-mapper-libs = %{device_mapper_version}-%{release}

%description -n device-mapper-devel
This package contains files needed to develop applications that use
the device-mapper libraries.

%package -n device-mapper-libs
Summary: Device-mapper shared library
Version: %{device_mapper_version}
Release: %{release}
License: LGPLv2.1
Group: System/Libraries
Obsoletes: device-mapper < 1.02.17-6

%description -n device-mapper-libs
This package contains the device-mapper shared library, libdevmapper.

%prep
%setup -q -n LVM2.%{lvm2_version}

%build
%define _exec_prefix ""
%configure --with-user= --with-group= --with-device-uid=0 --with-device-gid=6 --with-device-mode=0660 --enable-pkgconfig
%define _exec_prefix /
make device-mapper

%install
rm -rf $RPM_BUILD_ROOT
make install_device-mapper DESTDIR=$RPM_BUILD_ROOT usrlibdir=$RPM_BUILD_ROOT/usr/%{_lib}
sed -i 's/ (.*)//g' $RPM_BUILD_ROOT%{_libdir}/pkgconfig/*.pc

%clean
rm -rf $RPM_BUILD_ROOT

%post -n device-mapper-libs -p /sbin/ldconfig

%postun -n device-mapper-libs -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%doc COPYING COPYING.LIB INSTALL README VERSION_DM WHATS_NEW_DM
%attr(755,root,root) %{_sbindir}/dmsetup
%{_mandir}/man8/dmsetup.8.gz

%files -n device-mapper-devel
%defattr(-,root,root,-)
%attr(755,root,root) /%{_libdir}/libdevmapper.so
%{_includedir}/libdevmapper.h
%{_libdir}/pkgconfig/*.pc

%files -n device-mapper-libs
%attr(755,root,root) /%{_libdir}/libdevmapper.so.*


