# Fuzzy Controller for the Inverted Pendulum

A **Zero-Order Sugeno Fuzzy Inference System** that balances an inverted pendulum on a moving cart, built for **159.302 Artificial Intelligence – Assignment #2** (N.H. Reyes).

The simulation uses second-order derivative physics equations and a simple graphics library to model the full cart–pendulum dynamics. A built-in fuzzy logic engine provides trapezoidal membership functions and centroid defuzzification.

---

## Table of Contents

- [Overview](#overview)
- [Controller Design](#controller-design)
  - [Inputs](#inputs)
  - [Fuzzy Rules](#fuzzy-rules)
  - [Rule Outputs](#rule-outputs)
  - [Fuzzy Sets](#fuzzy-sets)
  - [Defuzzification](#defuzzification)
- [Calibration](#calibration)
- [Results](#results)
  - [Control Surface](#control-surface)
  - [Performance](#performance)
- [Running the Simulation](#running-the-simulation)
- [Project Structure](#project-structure)
- [Deliverables](#deliverables)
- [References](#references)

---

## Overview

The goal is to keep the pole upright and bring the cart to rest at the **centre of the platform** with the pole at **0° from vertical**, without the cart leaving the platform boundaries of **[-2.4 m, 2.4 m]**.

The controller is a zero-order Sugeno FIS: each rule outputs a constant force, and the final force is the weighted average of the fired rules.

## Controller Design

### Inputs

Following Yamakawa's design, the four state variables are combined into two inputs:

```
X = (A * theta) + (B * theta_dot)
Y = (C * x)     + (D * x_dot)
```

| Variable    | Meaning                                       |
|-------------|-----------------------------------------------|
| `x`         | Position of the cart                          |
| `x_dot`     | Horizontal velocity of the cart               |
| `theta`     | Angle of the pole with respect to the vertical |
| `theta_dot` | Angular velocity of the pole                  |
| `A, B, C, D`| Positive constants, tuned empirically         |

**Final coefficients:**

| A | B | C | D |
|---|---|---|---|
| | | | |

### Fuzzy Rules

The rule base follows the **13 rules** defined by Yamakawa (p. 517 of the paper below), optionally extended to a full **25-rule** (5×5) table.

<!-- Fill in the rule table, e.g.:
| X \ Y | NL | NS | ZE | PS | PL |
|-------|----|----|----|----|----|
| NL    |    |    |    |    |    |
| NS    |    |    |    |    |    |
| ZE    |    |    |    |    |    |
| PS    |    |    |    |    |    |
| PL    |    |    |    |    |    |
-->

### Rule Outputs

Because this is a zero-order Sugeno system, each linguistic output term is a constant force:

| Term | Output |
|------|--------|
| NL (Negative Large) | e.g. `-100` |
| NM (Negative Medium) | |
| NS (Negative Small) | |
| ZE (Zero) | `0` |
| PS (Positive Small) | |
| PM (Positive Medium) | |
| PL (Positive Large) | e.g. `100` |

### Fuzzy Sets

The membership functions are defined over each input's possible range, for example:

- `X`: [-4.0, 4.0]
- `Y`: [-4.0, 4.0]

They are implemented with the engine's trapezoidal membership functions (or any other membership function covered in class).

<!-- Add the membership function parameters for each linguistic term here. -->

### Defuzzification

Defuzzification uses the centroid (weighted average) method supplied by the fuzzy engine.

## Calibration

The controller is tuned by adjusting:

- the input coefficients **A, B, C, D**
- the membership function parameters
- the rule output constants

until it balances the pendulum **smoothly**, stays inside the platform, and returns the cart to the centre with the pole at 0°.

<!-- Note your tuning process and observations here. -->

## Results

### Control Surface

`generateControlSurface()` (already called in `main`) applies the physics updates and writes the data points to `data_angle_vs_angle_dot.txt`. The surface has three axes:

- pole angle
- pole angular velocity
- force output by the fuzzy controller

**To plot it in MS-Excel:** import the data, **delete the zero in the upper-left cell** (it exists only to align the columns), then insert a 3D surface chart.

<!-- ![Control surface](docs/control_surface.png) -->

### Performance

Tested by entering different initial pole angles at the command prompt (the program converts the input to radians). Larger initial angles are harder for the controller.

| Metric (at `x = 1`) | Value |
|---------------------|-------|
| Largest (most positive) initial angle handled |  |
| Smallest (most negative) initial angle handled | |
| Balancing duration | |

A run counts as successful if the cart stays within [-2.4 m, 2.4 m] and the pole does not fall.

## Running the Simulation

1. Build the project with the supplied makefile:
   ```bash
   make
   ```
2. Run the executable.
3. Type the initial pole angle (in degrees) at the prompt and press **Enter**. The simulation then runs.

> **Note:** Code blocks marked in the start-up source as part of the system dynamics must not be changed.

## Project Structure

```
.
├── src/                          # Simulation + fuzzy controller source (*.cpp, *.h)
├── makefile
├── data_angle_vs_angle_dot.txt   # Generated control surface data
├── control_surface.xlsx          # 3D control surface plot
├── checklist_ID.xlsx             # Completed assignment checklist
└── docs/
    └── fuzzy_system_report.pdf   # Design documentation
```

## Deliverables

- [ ] Full source code of the fuzzy controller and simulation (`*.cpp`, `*.h`, `makefile`)
- [ ] `checklist_ID.xlsx` with the largest handled angle recorded
- [ ] Typed fuzzy system report (Word/PDF) covering inputs, rules, fuzzy sets, rule outputs and defuzzification, written to the *Algorithm Documentation Guide*
- [ ] Control surface Excel file (angle vs. angular velocity)

**Before submitting:** delete all object and executable files, then scan the remaining files with Microsoft Defender using the latest virus definitions.

**Marking:** Documentation 15% · Fuzzy system implementation & calibration 85%

## References

- T. Yamakawa, *"A Fuzzy Inference Engine in Nonlinear Analog Mode and Its Application to a Fuzzy Logic Control."* (Rules and inputs: p. 517.)
- 159.302 lecture slides and video lecture on the fuzzy logic engine.
