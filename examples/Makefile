export F2C = ../../fsmlc	# the path of the FSML compiler from the single example directory

EXAMPLES = toy_decoder alarm # add more here


.PHONY: subdirs $(EXAMPLES)
subdirs: $(EXAMPLES)

$(EXAMPLES):
	$(MAKE) -C $@

clean:
	for d in $(EXAMPLES) ; do make --directory=$$d clean ; done