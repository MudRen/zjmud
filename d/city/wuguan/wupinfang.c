//wupinfang.c by river
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "��Ʒ��");
        set("long", @LONG
��������ݵ���Ʒ�������ݾͿ���һ������ӣ�������������ط����˸�
����Ʒ����������Ĺܼ��Ǻ����渺��ģ�һЩ�����ں͹���Ʒ���ߵ�������
�⿲˵��ʲô��
LONG
        );

        set("exits", ([
                "northwest" : __DIR__"dating",
        ]));

        set("no_fight",1);

        set("objects", ([
                   __DIR__"npc/dizi6" : 1,
        ]));

        setup();
}
