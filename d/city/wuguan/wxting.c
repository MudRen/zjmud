//wxting.c ��ϼͤ 

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIB"��ϼͤ"NOR);
        set("long", @LONG
����һ������ɫ���������Ƕ�������Сͤ���������ھ�����ϲ��������
���£���ϲ��������������ͤ����Χ����Ҷ���裬��ʯ���ţ��滨��ݣ�����
���ɴ�أ����õ���Ϊ���ţ�͸��һ�����£����ƾ����续������������ɽ��
LONG);       

	//set("outdoors","���");
	set("no_fight",1);
        set("exits", ([
            "west" : __DIR__"xiaojing2", 
            "south" : __DIR__"jiashan",              
        ]));       
 
        setup();
}
