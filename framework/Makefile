PROJECT=Framework.so
CXX=g++
OPTS=-c -g -Wall -std=c++0x -D_GLIBCXX_DEBUG 

# folder structure
SRCDIR = src
OBJDIR = obj
INCDIR = -Iinclude \
	 $(shell pkg-config --cflags python3) \
         -I/usr/local/include \

LDFLAGS= $(shell xml2-config --libs) \
	 $(shell xslt-config --libs) \
	 $(shell pkg-config --libs python3) \
	 -lboost_python3 \
	 -lboost_system \

INCLUDEPATH= `xml2-config --cflags` \
	     `xslt-config --cflags` \
	     $(INCDIR) 

SRCS := $(shell find $(SRCDIR) -name '*.cpp')
SRCDIRS := $(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# link object files
$(PROJECT): buildrepo $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -shared -o $@

# create object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(OPTS) $(INCLUDEPATH) $< -fPIC -o $@

clean:
	rm $(PROJECT) $(OBJDIR) -Rf

buildrepo:
	@$(call make-repo)

#create obj directory structure
define make-repo
mkdir -p $(OBJDIR)
for dir in $(SRCDIRS); \
	do \
	mkdir -p $(OBJDIR)/$$dir; \
	done
endef
