=============
xtal::control
=============

# Current Scope

The current implementation only specializes `defer` in order to provide implicit conversion from the underlying type.
Thus `control` acts as a transparent proxy, and the basis for types like `xtal::message::*` that implicitly produce their payload.

# Future Scope

The branch `feature/idempotent` explores the type-encoding of signal-conditioning operators like
`puncture`/`impurge` and `truncate`/`impurge`.
These operators follow a subset relationship such that e.g. `puncture<1 + N>: puncture<N>`,
and can be mixed in order to desribe the target domain.

The aim is to be able to apply additional conversions that are either
idempotent (in which case no action is taken) or further specialized (retaining the state of existing conversions).
