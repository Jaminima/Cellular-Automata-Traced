# Tracing a [Cellular Automaton](https://en.wikipedia.org/wiki/Cellular_automaton)
Visual artifacts such as ghosting are due to the gif encoder used.

## First B/W Rendering
Automata composes of simple booleans to store state.</br>
Renderer uses very a simple fixed ray marching algorihm.</br>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/1.gif" alt="" width="">

## Flat Rendering of Squares
Automota booleans swapped for RGB values.</br>
Renderer updated to support the new color space.</br>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/2.gif" alt="" width="">

## Squares Have Visible Depth
By reducing the increment size of the ray marching we can more accuratley detect collisions.</br>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/3.gif" alt="" width="">

## Smaller Rendering Steps
Further reduce incrment to get a finer quality of image.</br>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/4.gif" alt="" width="">

## Render Using More Efficient Technique
By detecting possible {x,y,z} intersects we can ensure that each ray march will be calculating a unique collision.</br>
Rather than possibly hitting the same empty square many times over while marching through its volume.</br>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/5.gif" alt="" width="">

## Cellular Rules are Applied
Simple rules are applied to each square every second, using their neighbours states to determine its own.</br>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/6.gif" alt="" width="">

## View Distance Effect More Visible
A thatched grid pattern becomes visible on squares at the edge of the render distance.</br>
The exact cause of this is unkown (for now).</br>
<img title="" src="https://github.com/Jaminima/Cellular-Automata-Traced/blob/main/Demo-Clips/7.gif" alt="" width="">
