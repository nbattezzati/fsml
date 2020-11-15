export F2C = ../../fsmlc	# the path of the FSML compiler from the single example directory

EXAMPLES = toy_decoder # add more here


.PHONY: subdirs $(EXAMPLES)
subdirs: $(EXAMPLES)

$(EXAMPLES):
	$(MAKE) -C $@

clean:
	$(MAKE) clean -C $(EXAMPLES)