//xiangfang1.c ���᷿

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIY"���᷿"NOR);
        set("long", @LONG
�����ǹ������������ݷ���ס�Ķ��᷿��͸��һ�����˵ķ��㣬������
���������ڷ����һ�ǰڷ���һ����ױ̨��̨�ϰ���һЩŮ���õ���֬�ۺ���
��ͿĨ�촽����ۣ��Լ�һƿ��¶�������߾��������ˡ�
LONG
        );        	

        set("exits", ([
               "east" : __DIR__"xiangfang2",    
	       "west" : __DIR__"zoulang3",
        ]));
	set("no_fight",1);
        set("objects", ([
              __DIR__"npc/dizi3" : 1,
        ]));

        setup();
}
