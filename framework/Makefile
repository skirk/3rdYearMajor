PROJECT=Framework
CXX=g++
OPTS=-c -Wall


# folder structure
SRCDIR = src
OBJDIR = obj
INCDIR = include

LDFLAGS= `xml2-config --libs`

INCLUDEPATH= `xml2-config --cflags` \
	    	-I$(INCDIR) 

SRCS := $(shell find $(SRCDIR) -name '*.cpp')
SRCDIRS := $(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# link object files
$(PROJECT): buildrepo $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

# create object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(OPTS) $(INCLUDEPATH) $< -o $@

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
