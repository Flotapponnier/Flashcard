CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS =

SRCDIR = src
INCDIR = includes
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

TARGET = flashcard
CLEAN_TARGETS = $(TARGET) $(OBJDIR)/*.o

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

.PHONY: all clean clean_all

all: $(TARGET)

clean:
	rm -f $(CLEAN_TARGETS)

clean_all: clean
	rm -f $(TARGET)

