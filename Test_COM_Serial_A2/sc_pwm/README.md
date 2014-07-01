XCORE Multi Channel PWM SOFTWARE COMPONENT
===============
<img align="left" src="https://s3-eu-west-1.amazonaws.com/synapticon-resources/images/logos/synapticon_fullname_blackoverwhite_280x48.png"/>
<img align="left" src="http://s27.postimg.org/higfoxmn7/xmos_logo_reduced.png"/>
<br/>
<br/>

The Pulse Width Modulation(PWM) components generates a number PWM signals using either one multibit port or a group of 1-bit ports.

The components will run in a par with the following function which does not terminate. A single function starts the pwm server and passes it a channel with 
which it will communicate with the client, a clock block required for the clocking of the required ports, an array of ports on which the pwm signals will be generated, and the number of ports in the array. 

The current stable version of the component that Synapticon offers just includes possibilities for a 6-port symmetrical PWM generation.
In order to access to obtain greater feature you might check out the develop branch, where other PWM applications are offered but their
stability is not guaranteed.

<table >
<tr>
  <td width="150px" height="30px">Latest release: </td>
  <td width="300px"><a href="https://github.com/synapticon/sc_sncn_ctrlproto/releases/tag/v0.9-beta">1.0.0rc0</a></td>
</tr>
<tr>
  <td height="30px">Maintainer:</td>
  <td><a href="mailto:support@synapticon.com">support@synapticon.com</a</td>
</tr>
</table> 

Key Features
---------
  * The components can be configured for Leading edge, Trailing edge and Center edge variations
  * Configurable timestep, resolution
  * 6-port symmetrical PWM generation


Further information
---------
  * sc_pwm DOCUMENTATION. (Coming soon!).

Known Issues
---------
  * None

Required software (dependencies)
---------
  * None

Changelog
---------

  * 1.0.0

  	* Initial release

License
---------

Please see [LICENSE](https://github.com/synapticon/sc_pwm/blob/master/LICENSE.dox).
