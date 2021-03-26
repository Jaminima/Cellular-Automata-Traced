# Tracing a [Cellular Automaton](https://en.wikipedia.org/wiki/Cellular_automaton)

Visual artifacts such as ghosting are due to the gif encoder used.

## The Evolution in pictures

<details>
  <summary>First B/W Rendering</summary>
  <p>Automata composes of simple booleans to store state.</br>
Renderer uses very a simple fixed ray marching algorihm.</p>
  <img title="" src="./Demo-Clips/1.gif" alt="" width=""/>
</details>

<details>
  <summary>Flat Rendering of Squares</summary>
  <p>
Automota booleans swapped for RGB values.</br>
Renderer updated to support the new color space.</p>
<img title="" src="./Demo-Clips/2.gif" alt="" width=""/>

</details>

<details>
  <summary>Squares Have Visible Depth</summary>
  <p>
By reducing the increment size of the ray marching we can more accuratley detect collisions.
</p>
<img title="" src="./Demo-Clips/3.gif" alt="" width=""/>
</details>

<details>
  <summary>Smaller Rendering Steps</summary>
  <p>
Further reduce incrment to get a finer quality of image.
</p>
<img title="" src="./Demo-Clips/4.gif" alt="" width=""/>
</details>

<details>
  <summary>Render Using More Efficient Technique</summary>
  <p>
By detecting possible {x,y,z} intersects we can ensure that each ray march will be calculating a unique collision.
Rather than possibly hitting the same empty square many times over while marching through its volume.</p>
<img title="" src="./Demo-Clips/5.gif" alt="" width=""/>

</details>

<details>
  <summary>Cellular Rules are Applied</summary>
  <p>
Simple rules are applied to each square every second, using their neighbours states to determine its own.</br></p>
<img title="" src="./Demo-Clips/6.gif" alt="" width=""/>
</details>

<details>
  <summary>View Distance Effect More Visible</summary>
  <p>
A thatched grid pattern becomes visible on squares at the edge of the render distance.</br>
The exact cause of this is unkown (for now).</br></p>
<img title="" src="./Demo-Clips/7.gif" alt="" width=""/>
</details>

<details>
  <summary>More Visible Rules</summary>
  <p>
Cells dissapear and new white cells appear into the world.</p>
<img title="" src="./Demo-Clips/8.gif" alt="" width=""/>
</details>

<details>
  <summary>Average Color for new cells</summary>
  <p>
Brand new cells use the average color of its neighbours.</p>
<img title="" src="./Demo-Clips/9.gif" alt="" width=""/>
</details>

<details>
  <summary>World Border</summary>
  <p>
Border Effect at the edge of the world</p>
<img title="" src="./Demo-Clips/10.png" alt="" width=""/>
</details>

<details>
  <summary>Chaoticly Growing Automota</summary>
  <p>
A rather interesting growth from a small original set of cells.</p>
<img title="" src="./Demo-Clips/11.gif" alt="" width=""/>
</details>

## Reduced Tracing Aliasing

To allow reduced tracing to function, it is neccesarry to fill in blanks around each ray. The pattern in which this is done has been through several itterations. Shown in order below.</br>
<img title="" src="./Demo-Clips/Reduced-Ray/PxlV1.png" alt="" width="" height="300px"/>
<img title="" src="./Demo-Clips/Reduced-Ray/PxlV2.png" alt="" width="" height="300px"/>
<img title="" src="./Demo-Clips/Reduced-Ray/PxlV3.png" alt="" width="" height="300px"/>
