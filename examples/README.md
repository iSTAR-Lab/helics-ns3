# Examples

Here's a quick overview of the examples and what they are showing. If you have improvements for the examples,
PRs are welcome.

The general process for running the examples is start up a `helics_broker` that expects two federates to
connect, then start the matching `ns3-*` and `fed-*` example program -- for example, `ns3-filter` and
`fed-filter`.

* `fed-sndrcv`/`ns3-sndrcv`: an example showing how messages sent using a HELICS endpoint can be
   sent across a simulated ns-3 network as an intermediary. Uses the `StaticSink` and `StaticSource`
   helics-ns3 applications to create HELICS endpoints that tie into the ns-3 network.
* `fed-filter`/`ns3-filter`: an example showing how messages sent using a HELICS endpoint can be
   intercepted using a HELICS filter and sent across a simulated ns-3 network. Uses the `Filter`
   helics-ns3 application to intercept messages and send them through the ns-3 network instead.
* `fed-pubsub`: a basic example showing how to use the `helics_federate` to register
   publications and subscriptions. Can be run with the `ns3-sndrcv` federate. Integrating
   these with the simulated ns-3 network is not shown as it is very use case dependent.
   Some (unreleased) use cases have written custom `ns3::Application` classes.

## Running the examples

From the top-level ns-3 directory, after building with `--enable-examples`, run each command in its own
terminal (or in the background):

```bash
helics_broker -f 2
./ns3 run --no-build ns3-sndrcv
./ns3 run --no-build fed-sndrcv
```

Replace `ns3-sndrcv`/`fed-sndrcv` with `ns3-filter`/`fed-filter` for the filter example. To run
`fed-pubsub` by itself, start the broker with `-f 1`.

`new-ns3-filter` is a variant of `ns3-filter` that creates its federate, endpoints, and reroute filters from a
JSON configuration file (default `contrib/helics/examples/ns3-config.json`, change it with `--config=<file>`); it
can also be run with `fed-filter`.

The ns-3 examples accept `--broker`, `--coretype` (default `zmq`), and `--coreinit` options for connecting to a
broker that is not running with default settings, and the `fed-*` examples accept the standard HELICS federate
options (e.g. `--broker`, `--coretype`, `--coreinit`); use `--help` to see the full list of options.
