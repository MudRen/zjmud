// /guanwai/xiaowu.c

inherit ROOM;

void create()
{
    set("short", "Сé��");
    set("long", @LONG
����һ���ó���ɽ��ľ�ݳɵ�С�ݣ����ڴ�ɨ�ĺܸɾ��������
ǽ���Ϲ�������Ƥ��ѩ����һ��СС����������һ����״󺺡�����
����һ��С�ţ������ƺ����ж��졣
LONG );
    set("exits", ([
	"south" : __DIR__"xiaoyuan",
	"north" : __DIR__"houyuan",
    ]));
    set("objects", ([
	CLASS_D("hu") + "/hufei" : 1,
    ]));
    setup();
}

