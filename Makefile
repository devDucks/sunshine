ifeq (, $(shell which pipenv))
$(error "No pipenv in $(PATH)    You need to install pipenv for your OS, exiting.")
endif

.PHONY = bootstrap

bootstrap:
	@pipenv install

.PHONY = test

test: bootstrap
	@pipenv run pytest -v -s
