# LintLord

This is an opinionated code style checker cor C++ that evaluates your codebase with an oppressive rule (regex.) LintLord has a few simple demands...

- Variables and parameters should use camelCase
- Constants should be in ALL_CAPS with underscores
- Functions should do one thing and do it well; every function should either be pure or void
- Don't create a variable for one use; just use a value
- Keep functions small, preferably under 20 lines
- Avoid code duplication
- Avoid deep nesting (16 spaces max)
- Where you throw, you must catch