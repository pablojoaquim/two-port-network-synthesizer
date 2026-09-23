# Cyborg C++ Project Template

A reusable C/C++ project template for building software using a human-led, AI-assisted engineering workflow with GitHub Copilot.

The template provides a standard project structure, build and test infrastructure, documentation conventions, and a workflow for developing software incrementally with AI assistance.

---

## Table of Contents

- [Cyborg C++ Project Template](#cyborg-c-project-template)
  - [Table of Contents](#table-of-contents)
  - [About](#about)
  - [Features](#features)
  - [Cyborg Workflow](#cyborg-workflow)
  - [Roles and Responsibilities](#roles-and-responsibilities)
    - [Human](#human)
    - [GitHub Copilot](#github-copilot)
  - [Tech Stack](#tech-stack)
  - [Project Structure](#project-structure)
    - [Main directories](#main-directories)
    - [Key documents](#key-documents)
  - [Getting Started](#getting-started)
    - [Clone the repository](#clone-the-repository)
    - [Install dependencies](#install-dependencies)
      - [Windows (MSYS2 / MinGW)](#windows-msys2--mingw)
      - [Linux](#linux)
  - [Build \& Run](#build--run)
    - [Build](#build)
    - [Run the executable](#run-the-executable)
  - [Running Tests](#running-tests)
  - [Code Coverage](#code-coverage)
  - [Configuration](#configuration)
  - [Using the Template](#using-the-template)

---

## About

This repository is a reusable starting point for C/C++ projects developed using the Cyborg Workflow.

It provides the engineering infrastructure needed to build, test, document, and maintain a project while keeping product-specific decisions outside the template.

The template is intentionally lightweight. Project-specific requirements, architecture, design decisions, implementation tasks, and validation criteria are created as part of the development workflow.

---

## Features

* Human-led, AI-assisted development workflow
* GitHub Copilot integration
* Requirements and design documentation
* Software Design Document (SDD)
* Architecture documentation
* Task-based development
* Unit testing
* Code coverage
* Modular C/C++ project structure
* Make-based build system

---

## Cyborg Workflow

This project follows a **human-led, AI-assisted engineering workflow**.

The human remains responsible for understanding the problem, defining the requirements, making engineering decisions, reviewing the implementation, and accepting the final result.

GitHub Copilot acts as an engineering assistant that helps with analysis, design proposals, implementation, testing, refactoring, and documentation.

The development flow is:

```text
Problem
   ↓
README
   ↓
SDD
   ↓
Architecture
   ↓
Backlog
   ↓
Task
   ↓
Copilot
   ↓
Human Review
   ↓
Tests
   ↓
Done
```

A completed task does not necessarily mean that the project is finished. New requirements, findings, defects, or architectural changes can create new tasks and start another development cycle.

---

## Roles and Responsibilities

### Human

The human is responsible for:

* Problem definition
* Requirements
* Scope
* Architecture decisions
* Technical decisions
* Prioritization
* Code review
* Validation
* Final acceptance

### GitHub Copilot

Copilot assists with:

* Problem analysis
* Design proposals
* Implementation
* Test development
* Refactoring
* Documentation
* Code exploration
* Identifying potential issues

Copilot must work within the requirements, architecture, and constraints defined by the project.

---

## Tech Stack

| Component    | Technology             |
| ------------ | ---------------------- |
| Language     | C / C++                |
| Build System | Make                   |
| Testing      | Unit testing framework |
| Coverage     | gcov / gcovr           |
| AI Assistant | GitHub Copilot         |

---

## Project Structure

```text
cyborg-cpp-project-template/
│
├── .github/
│   └── copilot-instructions.md
│
├── assets/
│
├── backlog/
│   └── tasks/
│
├── docs/
│   ├── sdd.md
│   └── architecture/
│
├── src/
├── test/
├── tools/
├── utils/
│
├── .gitignore
├── LICENSE
├── Makefile
├── README.md
└── backlog.md
```

### Main directories

| Directory            | Purpose                                 |
| -------------------- | --------------------------------------- |
| `.github/`           | GitHub and Copilot project instructions |
| `assets/`            | Project assets and supporting files     |
| `backlog/`           | Task definitions                        |
| `docs/`              | Project documentation                   |
| `docs/architecture/` | Detailed architecture documentation     |
| `src/`               | Production source code                  |
| `test/`              | Unit and integration tests              |
| `tools/`             | Development and engineering tools       |
| `utils/`             | Reusable utilities                      |

### Key documents

| File                              | Purpose                                         |
| --------------------------------- | ----------------------------------------------- |
| `README.md`                       | Project overview and entry point                |
| `docs/sdd.md`                     | Software Design Document                        |
| `backlog.md`                      | Project backlog                                 |
| `backlog/tasks/`                  | Individual task definitions                     |
| `.github/copilot-instructions.md` | Instructions and constraints for GitHub Copilot |

---

## Getting Started

### Clone the repository

```bash
git clone https://github.com/yourname/project.git
cd project
```

> Replace the repository URL and project name with the project created from this template.

### Install dependencies

#### Windows (MSYS2 / MinGW)

```bash
pacman -S mingw-w64-x86_64-gcc gcovr
```

#### Linux

```bash
sudo apt install build-essential gcovr
```

---

## Build & Run

### Build

```bash
make
```

### Run the executable

```bash
make run
```

---

## Running Tests

Build the test targets:

```bash
make tests
```

Run the tests:

```bash
make run-tests
```

---

## Code Coverage

Generate the coverage report:

```bash
make coverage
```

The report is generated at:

```text
build/coverage/coverage.html
```

---

## Configuration

Common Makefile variables that can be customized:

| Variable    | Description             |
| ----------- | ----------------------- |
| `SRC_DIRS`  | Source code directories |
| `TEST_DIRS` | Test code directories   |

Project-specific configuration should be documented in the appropriate project documentation rather than added to this template.

---

## Using the Template

When creating a new project from this template:

1. Define the problem and project scope.
2. Adapt this `README.md` to describe the new project.
3. Define the software design in `docs/sdd.md`.
4. Document relevant architecture information in `docs/architecture/`.
5. Create and prioritize items in `backlog.md`.
6. Break backlog items into individual tasks.
7. Use GitHub Copilot to assist with one task at a time.
8. Review and validate the generated implementation.
9. Run the relevant tests.
10. Mark the task as done only after human validation.

The template provides the engineering framework. **The project defines the product.**
