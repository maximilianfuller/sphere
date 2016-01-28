#include "util/CommonIncludes.h"
#include "util/ResourceLoader.h"
#include "view.h"
#include <QApplication>
#include <QKeyEvent>
#include <QGLFormat>

/** Static methods **/

QGLFormat View::getFormat()
{
    QGLFormat glFormat;
    glFormat.setVersion( 3, 3 );
    glFormat.setProfile( QGLFormat::CoreProfile );
    glFormat.setSampleBuffers( true );
    return glFormat;
}

/** Instance methods **/

View::View(QWidget *parent) : QGLWidget(getFormat(), parent)
{
    // View needs all mouse move events, not just mouse drag events
    setMouseTracking(true);

    // Hide the cursor since this is a fullscreen app
    setCursor(Qt::BlankCursor);

    // View needs keyboard focus
    setFocusPolicy(Qt::StrongFocus);

    // The game loop is implemented using a timer
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));

    for (int i = 0; i < FRAMES_TO_AVERAGE; i++) {
        frameTimes[i] = 0;
    }
    frameIndex = 0;

    // Setup camera
    glm::vec2 ratio = glm::vec2(16.f, 9.f);
    m_cam = new Camera(ratio);
}

View::~View()
{
    delete m_cam;
}

void View::initializeGL()
{
    /* All OpenGL initialization *MUST* be done during or after this
     * method. Before this method is called, there is no active OpenGL
     * context and all OpenGL calls have no effect. */

    /* Initialize glew */

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if ( GLEW_OK != err ) {
        // Problem: glewInit failed, something is seriously wrong.
        std::cerr << "Something is very wrong, glew initialization failed." << std::endl;
    }

    std::cout << "Using GLEW " <<  glewGetString( GLEW_VERSION ) << std::endl;

    /* Start engine time */

    // Start a timer that will try to get 60 frames per second (the actual
    // frame rate depends on the operating system and other running programs)
    time.start();
    timer.start(1000 / 60);

    /* Initialize devices */

    // Center the mouse, which is explained more in mouseMoveEvent() below.
    // This needs to be done here because the mouse may be initially outside
    // the fullscreen window and will not automatically receive mouse move
    // events. This occurs if there are two monitors and the mouse is on the
    // secondary monitor.
    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

    /* General GL setup */

    // Enable depth testing, so that objects are occluded based on depth instead of drawing order.
    glEnable(GL_DEPTH_TEST);

    // Enable back-face culling, meaning only the front side of every face is rendered.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Specify that the front face is represented by vertices in counterclockwise order (this is
    // the default).
    glFrontFace(GL_CCW);

    // Load shaders
    m_shader = ResourceLoader::loadShaders(":/shaders/shader.vert",":/shaders/shader.frag");
}

void View::paintGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1,1,1);

    /* Rendering code */

    // Update camera
    m_cam->sendTransforms(m_shader);
}

void View::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    glm::vec2 size = glm::vec2(static_cast<float>(w), static_cast<float>(h));
    m_cam->setRatio(size);
}

void View::mousePressEvent(QMouseEvent *event)
{
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    /* Re-center the mouse */

    // Get deltas
    int deltaX = event->x() - width() / 2;
    int deltaY = event->y() - height() / 2;

    // Avoid infinite loop
    if (!deltaX && !deltaY)
    {
        return;
    }

    // Set mouse position. Triggers mouse move event
    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

    /* TODO: Handle mouse movements */
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
}

void View::wheelEvent(QWheelEvent *event)
{
}

void View::keyPressEvent(QKeyEvent *event)
{
    /* Handle keypresses */

    // Quit
    if (event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }

    /* TODO: handle other key presses */
}

void View::keyReleaseEvent(QKeyEvent *event)
{
}

void View::tick()
{
    /* Record ups */

    // Get the number of seconds since the last tick (variable update rate)
    float seconds = time.restart() * 0.001f;

    frameTimes[frameIndex] = seconds;
    frameIndex = (frameIndex + 1) % FRAMES_TO_AVERAGE;
    fps = 0;

    for (int i = 0; i < FRAMES_TO_AVERAGE; i++) {
        fps += frameTimes[i];
    }

    fps /= FRAMES_TO_AVERAGE;
    fps = 1.f / fps;

    /* TODO: implement game update */

    /* Update */

    // Flag this view for repainting (Qt will call paintGL() soon after)
    update();
}
