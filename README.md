# Tracing a [Cellular Automaton](https://en.wikipedia.org/wiki/Cellular_automaton)

Visual artifacts such as ghosting are due to the gif encoder used.

<details>
  <summary><h2>First B/W Rendering</h2></summary>
  <p>Automata composes of simple booleans to store state.</br>
Renderer uses very a simple fixed ray marching algorihm.</p>
  <img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/1.gif" alt="" width=""/>
</details>

<details>
  <summary><h2>Flat Rendering of Squares</h2></summary>
  <p>
Automota booleans swapped for RGB values.</br>
Renderer updated to support the new color space.</p>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/2.gif" alt="" width=""/>

</details>

<details>
  <summary><h2>Squares Have Visible Depth</h2></summary>
  <p>
By reducing the increment size of the ray marching we can more accuratley detect collisions.
</p>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/3.gif" alt="" width=""/>
</details>

<details>
  <summary><h2>Smaller Rendering Steps</h2></summary>
  <p>
Further reduce incrment to get a finer quality of image.
</p>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/4.gif" alt="" width=""/>
</details>

<details>
  <summary><h2>Render Using More Efficient Technique</h2></summary>
  <p>
By detecting possible {x,y,z} intersects we can ensure that each ray march will be calculating a unique collision.
Rather than possibly hitting the same empty square many times over while marching through its volume.</p>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/5.gif" alt="" width=""/>

</details>

<details>
  <summary><h2>Cellular Rules are Applied</h2></summary>
  <p>
Simple rules are applied to each square every second, using their neighbours states to determine its own.</br></p>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/6.gif" alt="" width=""/>
</details>

<details>
  <summary><h2>View Distance Effect More Visible</h2></summary>
  <p>
A thatched grid pattern becomes visible on squares at the edge of the render distance.</br>
The exact cause of this is unkown (for now).</br></p>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/7.gif" alt="" width=""/>
</details>
