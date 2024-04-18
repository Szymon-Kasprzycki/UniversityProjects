# Simple CSS Processing Engine

**Author:**\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_, _Gdańsk University of Technology_

## Project Overview

- Goal: Write a simple CSS processing engine to parse CSS declarations and execute commands.
- CSS sections are interleaved with command sections from standard input.
- CSS blocks consist of selectors and attributes enclosed in curly braces.
- Attributes are separated by semicolons and consist of a name (property) and a value separated by a colon.
- Selectors are separated by commas.
- Commands begin with specific symbols and execute actions based on input parameters.

### CSS Parsing Rules

- CSS sections may contain selectors and attributes.
- Selectors are separated by commas and enclosed in curly braces.
- Attributes are separated by semicolons.
- Multiple occurrences of the same attribute name in a block are treated as a single occurrence, with the last value being significant.
- No nesting of blocks is allowed.
- Comments and @-type selectors are not supported.
- All values are treated as strings without semantic interpretation.

### Command Syntax

- `????`: Start of command section.
- `****`: Resume reading CSS.
- `?`: Print the number of CSS sections.
- `i,S,?`: Print the number of selectors for section number i.
- `i,A,?`: Print the number of attributes for section number i.
- `i,S,j`: Print the j-th selector for the i-th block.
- `i,A,n`: Print the value of the attribute with the name n for the i-th section.
- `n,A,?`: Print the total number of occurrences of attribute named n.
- `z,S,?`: Print the total number of occurrences of selector z.
- `z,E,n`: Print the value of the attribute named n for the selector z.
- `i,D,*`: Remove the entire section number i.
- `i,D,n`: Remove the attribute named n from the i-th section.

## Implementation Notes

- Selectors and attributes stored as lists.
- CSS sections stored in a doubly linked list.
- Utilize an array-based list structure with a constant size T for blocks.
- Efficiently allocate and deallocate memory for nodes and elements.
- Use counters to speed up operations and manage memory effectively.
