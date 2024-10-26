import '/flutter_flow/flutter_flow_util.dart';
import '/flutter_flow/instant_timer.dart';
import 'display_received_data_widget.dart' show DisplayReceivedDataWidget;
import 'package:flutter/material.dart';

class DisplayReceivedDataModel
    extends FlutterFlowModel<DisplayReceivedDataWidget> {
  ///  Local state fields for this component.

  String? data;

  ///  State fields for stateful widgets in this component.

  InstantTimer? receiveDataTimer;
  // Stores action output result for [Custom Action - receiveData] action in DisplayReceivedData widget.
  String? receivedData;

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    receiveDataTimer?.cancel();
  }
}
