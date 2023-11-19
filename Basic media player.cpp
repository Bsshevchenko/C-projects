#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

class SimpleMediaPlayer : public QWidget {
    Q_OBJECT

public:
    SimpleMediaPlayer(QWidget *parent = nullptr) : QWidget(parent) {
        mediaPlayer = new QMediaPlayer(this);
        videoWidget = new QVideoWidget(this);

        playButton = new QPushButton("Play", this);
        stopButton = new QPushButton("Stop", this);
        openButton = new QPushButton("Open", this);

        positionSlider = new QSlider(Qt::Horizontal, this);
        positionLabel = new QLabel("00:00", this);
        durationLabel = new QLabel(" / 00:00", this);

        connect(playButton, &QPushButton::clicked, this, &SimpleMediaPlayer::playClicked);
        connect(stopButton, &QPushButton::clicked, mediaPlayer, &QMediaPlayer::stop);
        connect(openButton, &QPushButton::clicked, this, &SimpleMediaPlayer::openFile);
        connect(positionSlider, &QSlider::sliderMoved, this, &SimpleMediaPlayer::setPosition);

        QHBoxLayout *controlLayout = new QHBoxLayout;
        controlLayout->addWidget(playButton);
        controlLayout->addWidget(stopButton);
        controlLayout->addWidget(openButton);
        controlLayout->addWidget(positionSlider);
        controlLayout->addWidget(positionLabel);
        controlLayout->addWidget(durationLabel);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(videoWidget);
        mainLayout->addLayout(controlLayout);

        setLayout(mainLayout);

        mediaPlayer->setVideoOutput(videoWidget);
        connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &SimpleMediaPlayer::updatePosition);
        connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &SimpleMediaPlayer::updateDuration);
    }

private slots:
    void playClicked() {
        if (mediaPlayer->state() == QMediaPlayer::PlayingState) {
            mediaPlayer->pause();
            playButton->setText("Play");
        } else {
            mediaPlayer->play();
            playButton->setText("Pause");
        }
    }

    void openFile() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Media File");
        if (!fileName.isEmpty()) {
            mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));
            playButton->setEnabled(true);
            stopButton->setEnabled(true);
        }
    }

    void setPosition(int position) {
        mediaPlayer->setPosition(position);
    }

    void updatePosition(qint64 position) {
        positionSlider->setValue(position);
        positionLabel->setText(formatTime(position));
    }

    void updateDuration(qint64 duration) {
        positionSlider->setRange(0, duration);
        durationLabel->setText(" / " + formatTime(duration));
    }

    QString formatTime(qint64 time) {
        int seconds = time / 1000;
        int minutes = seconds / 60;
        seconds %= 60;
        return QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
    }

private:
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *openButton;
    QSlider *positionSlider;
    QLabel *positionLabel;
    QLabel *durationLabel;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SimpleMediaPlayer player;
    player.setWindowTitle("Simple Media Player");
    player.setGeometry(100, 100, 800, 600);
    player.show();

    return app.exec();
}

#include "main.moc"
