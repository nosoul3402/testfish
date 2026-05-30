CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra

CATCHFISH_ROOT := ../cocos2d-x-2.1.5/projects/CatchFish
SOURCES := dev_verify.cpp \
	$(CATCHFISH_ROOT)/Classes/PublicModels/DataBase64Himi.cpp

.PHONY: all verify clean

all: verify

verify: dev_verify
	./dev_verify

dev_verify: $(SOURCES)
	$(CXX) $(CXXFLAGS) -I$(CATCHFISH_ROOT)/Classes/PublicModels $(SOURCES) -o $@

clean:
	rm -f dev_verify
