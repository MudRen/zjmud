//bingqiku.c by river

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
��������ݵı����⣬��Χ�ı������Ϸ��źܶ��������������ì��ꪵ�
ʮ�˰�����������롣һȺ��ݵ�����վ�ڼ�ǰ��ѡ�Լ����ֵı��С������
�����䳡�ˣ�����ܶ����������Ȼ����ء�
LONG
        );      	 
	
        set("exits", ([
               "north" : __DIR__"wuchang3",               
        ]));
        
        set("objects", ([
           __DIR__"obj/jia" : 1,
        ]));
	set("no_fight", 1);

        setup();
}
