// Room: /d/heimuya/pingdingzhou.c
inherit ROOM;

void create()
{
    set("short", "ƽ����");
    set("long", @LONG
ƽ�����ںӱ����ڣ��ݸ����󣬵��ش�Ҫ�壬ʮ����Ҫ��
�������ǵĿ��̴���Ƶ��������������½�ͽ���ֱײ������
ץ�ˣ�����ھ��ܣ�ȴ˿��û���ٸ��������
LONG );

    set("exits", ([
	"east" : __DIR__"road3",
	"west" : __DIR__"road2",
    ]));
    set("outdoors", "heimuya");
    set("no_clean_up", 0);
    setup();
  }
