// /guanwai/houyuan.c

inherit ROOM;

void create()
{
    set("short", "��Ժ");
    set("long", @LONG
���Ǻ��ҵĺ�Ժ����Ȼ���󣬵�����ʰ����Ϊ�������䣬������
���˳����Ĵ�ɨ��Ե�ʡ����������Ĵ������������澲һЩ������
������ȥ��һ��������ʯ�ӵ�С·������Ʈ�������㡣
LONG );
    set("exits", ([
	"south" : __DIR__"xiaowu",
	"north" : __DIR__"shizilu",
	"east"  : __DIR__"liangong",
	"west"  : __DIR__"jingxiu",
    ]));
    set("outdoor", "guanwai");
    setup();
}
