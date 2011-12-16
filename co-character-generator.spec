Summary: An automatic character generator for Chroniques Oubliées.
Name: co-character-generator
Version: 1.1
Release: 0
License: GPL
Group: Application/Tools
URL: http://co-character-creator.nigelj.com/
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
Requires: qt qt-x11
BuildRequires: qt-devel
%description
A Qt application to generate character for the Chronique Oubliées role playing game.

%prep
%setup 

%build
qmake-qt4
make

%install
rm -rf $RPM_BUILD_ROOT
qmake-qt4
make install INSTALL_ROOT=$RPM_BUILD_ROOT 

%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%attr(0755,root,root) /bin/co-creator
/usr/share/doc/%{name}-%{version}/COPYING
/usr/share/doc/%{name}-%{version}/LISEZMOI.txt

%changelog
* Sat Oct  1 2011 Pierre Amadio <melmoth@fedora14.localdomain> - character-generator
- Initial build.

