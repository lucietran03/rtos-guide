# CLAUDE.md

# Realtime Systems Engineering Learning Assistant

## Project Objective

This repository is not just a collection of lecture materials.

Its primary purpose is to build an interactive learning website that teaches the Realtime Systems Engineering course.

The website should function as a personal learning assistant that explains concepts in a clear, structured, beginner-friendly manner.

---

# Target Audience

The audience is the repository owner.

Assume:

- Software Engineering student.
- Already knows Java, Python, basic C.
- Has forgotten a lot of C syntax.
- New to Realtime Systems, QNX Neutrino RTOS and Embedded Systems.
- Prefers understanding concepts rather than memorising slides.
- Wants practical explanations before theoretical definitions.

---

# Teaching Language

The entire explanation should be written in Vietnamese.

However,

**ALL technical terms MUST remain in English.**

Examples:

✅ Process
✅ Thread
✅ Priority Inheritance
✅ Scheduling
✅ Message Passing
✅ Mutex
✅ Semaphore
✅ Deadlock
✅ Interrupt
✅ Timer
✅ Channel
✅ Pulse
✅ QNX Neutrino
✅ Momentics IDE

Do NOT translate technical terminology into Vietnamese.

---

# Learning Philosophy

When generating learning content:

Never simply rewrite lecture slides.

Instead,

1. Read ALL available materials related to the topic.

This includes:

- lecture slides
- lecture transcript
- lab sheet
- tutorial sheet
- sample code
- provided source code
- assignment specification (if available)
- additional notes
- instructor examples

Do not rely on only one source.

Combine all information before generating explanations.

---

2.

Prioritise explaining

WHY

before

HOW

Example:

Instead of

"This is a Mutex."

Explain

"Why Mutex is needed before introducing what a Mutex is."

---

3.

Whenever possible,

use practical examples.

Examples:

- Bank account
- Restaurant
- Traffic light
- CPU cores
- Cars
- Queue
- Warehouse robots
- ATM
- Operating system

Avoid abstract textbook-only explanations.

---

4.

Always connect lecture concepts with lab exercises.

For every important concept,

explain:

- Where it appears in the lecture
- Where it appears in the lab
- Why the lab is implemented that way
- What students should observe while running the code

---

5.

Whenever sample code exists,

explain the code line-by-line.

Explain

- what it does
- why it exists
- common mistakes
- expected output
- relation to lecture concepts

---

6.

For every Week,

generate learning notes based on ALL materials inside that Week.

Never ignore any file.

---

# Website Structure

The generated website should be modular.

Avoid large HTML files.

Split the content into reusable components whenever possible.

Example structure:

Week01/

    index.html

    overview.html

    lecture/

        scheduling.html

        interrupt.html

        qnx.html

    lab/

        setup.html

        task1.html

        task2.html

    examples/

        sample1.html

        sample2.html

    assets/

Week02/

...

The objective is to keep every page small and easy to edit.

---

# Website Design

DO NOT invent a new UI.

Instead,

reuse the design language from:

https://github.com/lucietran03/embedded-2

This repository should only be used as a design reference.

Follow:

- layout
- navigation
- component structure
- spacing
- typography
- styling
- color palette
- responsive behaviour
- animations

Do NOT copy learning content from that repository.

Only reuse the design philosophy.

---

# Shared Assets

The Embedded-2 repository already contains reusable assets.

Reuse whenever appropriate.

Examples:

- CSS
- JavaScript
- icons
- images
- reusable UI components
- layout templates

Copy only assets that improve consistency.

Avoid duplicating unnecessary files.

---

# Navigation

Every Week should contain:

Overview

↓

Lecture

↓

Lab

↓

Examples

↓

Summary

Users should always know where they are.

Breadcrumb navigation is encouraged.

---

# Learning Style

Avoid long paragraphs.

Instead,

Use

- diagrams
- tables
- callout boxes
- warning boxes
- tip boxes
- code blocks
- step-by-step explanation

The website should feel like an interactive textbook instead of lecture slides.

---

# Code Explanation

Whenever C code is presented,

Explain

- syntax
- memory behaviour
- pointer behaviour (if relevant)
- execution order
- output
- common mistakes

Never assume the reader remembers C.

---

# Lab Guidance

For every lab,

provide

- objective
- required knowledge
- preparation
- step-by-step walkthrough
- expected output
- troubleshooting
- common errors
- explanation of why each step is required

Do not only explain what commands to type.

Explain why.

---

# Visualisations

Whenever possible,

generate diagrams using HTML/CSS instead of images.

Examples:

- Process Scheduling
- Thread lifecycle
- Priority Queue
- Message Passing
- IPC
- Memory Layout

---

# Repository Behaviour

Whenever new materials are added,

re-read all files inside that Week before updating any generated content.

Do not overwrite manually written explanations unless necessary.

Prefer incremental updates.

---

# Content Accuracy

If lecture slides, transcript and lab disagree,

prioritise

1. Instructor explanation
2. Lab specification
3. Lecture slides

State any inconsistency clearly.

---

# Goal

The final result should resemble a high-quality interactive online textbook for the Realtime Systems Engineering course rather than a collection of lecture notes.

# Generation Rules

Whenever creating or modifying files:

- Preserve existing folder structure whenever possible.
- Create small reusable HTML components instead of one large page.
- Prefer incremental edits instead of regenerating the whole website.
- Do not duplicate content between pages.
- Extract repeated UI into reusable components.

# Before generating any page

Always inspect:

- current Week folder
- lecture slides
- lecture transcript
- lab sheet
- code samples
- existing generated HTML

before producing any explanation.
