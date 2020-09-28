
<html>
	<body>
<h1>Weapon Plugin</h1>


<h2>Links</h2>

  <ul>
     <li>  Facebook: https://tr-tr.facebook.com/kemalerdem09  </li>
     <li>  LinkedIn: https://www.linkedin.com/in/kemal-erdem-yilmaz-a2178411b  </li>
     <li>  Youtube: https://www.youtube.com/channel/UCmWrCX3Zpm0vbtH_-WHUSDw  </li>
     <li>  Unreal Engine Marketplace: https://unrealengine.com/marketplace/en-US/profile/Kemal+Erdem+YILMAZ  </li>
     <li>  Itch.io: https://elderdeveloper.itch.io/  </li>
  </ul>


  <h2>News</h2>
  
  <h2>Features</h2>
<p>
<ul>
	<li>Video displayed in-game</li>
	<li>Camera position tracked using fiducial markers, multiple independent sets of markers can be tracked at once</li>
	<li>Editable spatial configurations of markers </li>
	<li>Camera calibration</li>	
	<li>Multiple video sources: cameras, video files, network streams. Source can be switched using in-game UI</li>
	<li>Shadow simulation (assuming the scene is on a plane)</li>
</ul>
</p>
  
  <h2>Platforms</h2>
<ul>
<li>Windows</li>
<li>Linux</li>
<li>Android</li>
</ul>


<h2 name="install">Installation</h2>

<h3>Getting started - try the example project</h3>
<p>
<ul>
<li><a href="#downloads">Download the example project</a></li>
<li>Decompress the archive - and move <tt>AugmentedUnrealityEx</tt> to the location where you store your Unreal projects.</li>
<li>Launch Unreal Engine and open <tt>AugmentedUnrealityEx/AugmentedUnrealityEx.uproject</tt>.</li>

<li>Connect a camera and launch the game.</li>
<li>If the virtual object are not well aligned with the markers, perform <a href="#section_calibration">camera calibration</a>.</li>
</ul>
</p>

<figure>
<figcaption> Overview of elements visible in the example project: </figcaption>
	<img src="./Documentation/images/aur_overview.jpg" width="800" />
</figure>

<h3>Add plugin to an existing project:</h3>
<p>
<ul>
<li><a href="#downloads">Download the plugin</a></li>
<li>Decompress the archive - and move directory <tt>AugmentedUnreality</tt> to <tt>YourProject/Plugins</tt></li>
<li>Reopen your project</li>
<li>Add to your level: <tt>AURCameraActor</tt> to show the video and one of the <a href="boards">fiducial patterns</a>: <tt>PatternChessboard_A</tt>, <tt>PatternChessboard_B</tt>,  <tt>PatternCube</tt>, <tt>PatternSquare_A</tt>, <tt>PatternSquare_B</tt></li>
<li>Add a shadow plane actor if you want shadows cast on the surface under the markers</li>
<li>Run the game to generate pattern images. Then print the patterns from <tt>YourProject/Saved/AugmentedUnreality/Patterns</tt></li>
</ul>
</p>
		
		<h2>Project Status (IMPORTANT) </h2>

		<h2>How and Why ? </h2>

	</body>
</html>


