package com.ozsg.bladett

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Arrangement.Absolute.Center
import androidx.compose.foundation.layout.Column
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.drawscope.DrawScope
import androidx.compose.ui.input.pointer.consumeAllChanges
import androidx.compose.ui.input.pointer.pointerInput

import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.tooling.preview.Preview
import com.ozsg.bladett.ui.theme.BladettTheme

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.gestures.detectDragGestures
import androidx.compose.foundation.layout.*

import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.*



import androidx.compose.ui.input.pointer.consumeAllChanges
import androidx.compose.ui.input.pointer.pointerInput

import androidx.compose.ui.unit.dp
import androidx.lifecycle.lifecycleScope
import com.ozsg.bladett.ui.theme.BladettTheme
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlin.math.sqrt

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            BladettTheme {
                Surface(modifier = Modifier.fillMaxSize(), color = Color.Black) {
                    Column {
                        SolJoystick("Android")
                        SagJoystick(name = "bruh")
                    }
                }
            }
        }
    }
}

@Composable
fun SolJoystick(name: String) {
    var offsetX by remember { mutableStateOf(0f) }
    var offsetY by remember { mutableStateOf(0f) }
    var isDragging by remember { mutableStateOf(false) }

    val radius = 300f
    val maxDistance = 300f

    val lifecycleScope = rememberCoroutineScope()

    Column(

        modifier = Modifier
            .fillMaxSize()
            .offset(y = 100.dp)
            .background(Color.Transparent),

        verticalArrangement = Arrangement.Top,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Canvas(modifier = Modifier
            .size(200.dp)
            .pointerInput(Unit) {
                detectDragGestures(
                    onDragStart = {
                        isDragging = true
                    },
                    onDragEnd = {
                        isDragging = false
                        //offsetX = 0f
                        offsetY = 0f
                    }
                ) { change, dragAmount ->
                    val distance = sqrt(offsetX * offsetX + offsetY * offsetY)
                    if (isDragging && distance <= maxDistance) {
                        offsetX += dragAmount.x
                        offsetY += dragAmount.y
                        if (distance >= maxDistance) {
                            val scaleFactor = maxDistance / distance
                            offsetX *= scaleFactor
                            offsetY *= scaleFactor
                        }
                    }
                }
            }) {
            drawCircle(
                color = Color.Blue,
                radius = radius,
                center = Offset(size.width / 2, size.height / 2)
            )
            drawCircle(
                color = Color.Red,
                radius = 35f,
                center = Offset(size.width / 2 + offsetX, size.height / 2 + offsetY)
            )
        }

        //Text(text = "Hello $name!")
    }
}
@Composable
fun SagJoystick(name: String) {
    var offsetX by remember { mutableStateOf(0f) }
    var offsetY by remember { mutableStateOf(0f) }
    var isDragging by remember { mutableStateOf(false) }

    val radius = 300f
    val maxDistance = 300f

    val lifecycleScope = rememberCoroutineScope()

    Column(

        modifier = Modifier
            .fillMaxSize()
            .offset(y = -100.dp),

        verticalArrangement = Arrangement.Bottom,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Canvas(modifier = Modifier
            .size(200.dp)
            .pointerInput(Unit) {
                detectDragGestures(
                    onDragStart = {
                        isDragging = true
                    },
                    onDragEnd = {
                        isDragging = false
                        offsetX = 0f
                        offsetY = 0f
                    }
                ) { change, dragAmount ->
                    val distance = sqrt(offsetX * offsetX + offsetY * offsetY)
                    if (isDragging && distance <= maxDistance) {
                        offsetX += dragAmount.x
                        offsetY += dragAmount.y
                        if (distance > maxDistance) {
                            val scaleFactor = maxDistance / distance
                            offsetX *= scaleFactor
                            offsetY *= scaleFactor
                        }
                    }
                }
            }) {
            drawCircle(
                color = Color.Blue,
                radius = radius,
                center = Offset(size.width / 2, size.height / 2)
            )
            drawCircle(
                color = Color.Red,
                radius = 35f,
                center = Offset(size.width / 2 + offsetX, size.height / 2 + offsetY)
            )
        }

        //Text(text = "Hello $name!")
    }
}

@Preview(showBackground = true)
@Composable
fun DronePrev() {
    BladettTheme {
        SolJoystick("Android")
        SagJoystick(name = "bruh")
    }
}