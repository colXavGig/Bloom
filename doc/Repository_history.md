# Repository history management

History management in a repository means saving the changes applied to each
steps in a code repository to easily navigate and read the past changes.  
This document will attempt to explain the problems that our history management
system is trying to solve. and The structure and algorithm used to solve it.

## Requirements

1. Listing every steps and maintaining the order in which they were added to the
   history.
2. Inserting a step at the end of the history chain.
3. Ability to search and read a specific step of the history.
4. The ability to divide the history into multiple chains.
5. Merging two history chain divisions into one.

## Structure

The history will be representing by a tree.  

The usuage of a tree will help us represents those division into different branch
of this tree. When merging together, the branch can either be truly merged while
keeping the actual history or appending the branch to merge at the end of the
receiving branch without keeping the true history.

The usage of a tree will also let us keep in memory where two different history 
chain start to differ. This will help when merging two chains and merging the
history together, you dont need to merge the history before the division.

Finally, a tree will let us remove any need for duplication when managing multiple
divisions. It let us keep the relevant steps instead of keeping a copy of a 
duplicate step.

### Step structure

- root folder pointer: hash of the root folder
- metadata: 
      - time 
      - signature/user 
      - branchname
- step hash: hashed of the content of the step

### Tree structure

- 

