SUBDIRS = 
if WANT_DOM
  SUBDIRS += DOM SAX2DOM
endif
if WANT_XPATH
  SUBDIRS += XPath
endif

install:
	echo "Nothing to install here"

test:
	@for p in $(SUBDIRS); do \
	  cd $$p && make test; \
          cd ..; \
	done
