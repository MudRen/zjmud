#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "����");
    set("long", @LONG
���������������ľ���----�ɸ��ӣ��м�һ�Ŵ�����ǽ�Ϲ���һ
��ˮī����û��ʲô�ر����֮����
LONG );
    set("exits", ([
	"east" : __DIR__"zhulin",
    ]));

    set("objects",([
	 CLASS_D("shenlong")+"/su": 1,
	 __DIR__"npc/mujianping": 1,
	 __DIR__"npc/fangyi": 1,
    ]));
    setup();
}

