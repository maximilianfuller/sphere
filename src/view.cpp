#include "view.h"
#include "util/CommonIncludes.h"
#include "util/ResourceLoader.h"
#include "engine/Application.h"
#include "warmup/WarmupApplication.h"

#include <QApplication>
#include <QKeyEvent>
#include <QGLFormat>

/** Static methods **/

QGLFormat View::getFormat()
{
    QGLFormat glFormat;
    glFormat.setVersion(3, 2);
    glFormat.setProfile(QGLFormat::CoreProfile);
    glFormat.setSampleBuffers(true);
    return glFormat;
}

/** Instance methods **/

View::View(QWidget *parent) :
    QGLWidget(getFormat(), parent)
{
    // Enable all mouse events
    setMouseTracking(true);

    // Hide the cursor
    setCursor(Qt::BlankCursor);

    // Accept focus by tab and clicking
    setFocusPolicy(Qt::StrongFocus);

    // The game loop is implemented using a timer
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));

    // Initialize frame times
    for (int i = 0; i < FRAMES_TO_AVERAGE; i++) {
        frameTimes[i] = 0;
    }

    frameIndex = 0;
}

View::~View()
{
    delete app;
}

void View::initializeGL()
{
    /* Initialize glew */

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    glGetError();

    if ( GLEW_OK != err ) {
        // Problem: glewInit failed, something is seriously wrong.
        std::cerr << "Something is very wrong, glew initialization failed." << std::endl;
    }

    std::cout << "Using GLEW " <<  glewGetString( GLEW_VERSION ) << std::endl;

    /* Start engine time */

    // Timer at 60fps
    time.start();
    timer.start(1000 / 60);

    /* Initialize devices */

    // Center mouse
    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

    /* General GL setup */

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable back-face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Specify vertex order
    glFrontFace(GL_CCW);

    /* Setup application */
    app = new WarmupApplication(this);
}

void View::paintGL()
{
    // Specify screen clearing color
    glClearColor(0, 0, 0, 0);

    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Send paint event to application
    app->paint();
}

void View::resizeGL(int w, int h)
{
    // Resize viewport
    glViewport(0, 0, w, h);

    // Send resize event to application
    app->resize(w, h);
}

void View::tick()
{
    /* Record FPS */

    // Get the number of seconds since the last tick (variable update rate)
    float seconds = time.restart() * 0.001f;

    // Set current frame time
    frameTimes[frameIndex] = seconds;
    frameIndex = (frameIndex + 1) % FRAMES_TO_AVERAGE;
    fps = 0;

    // Accumulate frame times
    for (int i = 0; i < FRAMES_TO_AVERAGE; i++) {
        fps += frameTimes[i];
    }

    // Get average FPS
    fps /= FRAMES_TO_AVERAGE;
    fps = 1.f / fps;

    /* Update application and view */

    // Update application
    app->tick(seconds);

    // Flag this view for repainting
    update();
}

void View::mousePressEvent(QMouseEvent *event)
{
    app->mousePressEvent(event);
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    /* Decide whether or not to propagate event */

    // Deltas
    int deltaX = event->x() - width() / 2;
    int deltaY = event->y() - height() / 2;

    // Avoid infinite loop
    if (!deltaX && !deltaY)
    {
        return;
    }

    /* Send event to application */

    app->mouseMoveEvent(event);
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    app->mouseReleaseEvent(event);
}

void View::wheelEvent(QWheelEvent *event)
{
    app->wheelEvent(event);
}

void View::keyPressEvent(QKeyEvent *event)
{
    app->keyPressEvent(event);
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    app->keyReleaseEvent(event);
}
