//dating.c
inherit ROOM;

void create()
{
        set("short", "��ݴ���");
        set("long", @LONG
��������ݴ��������п�������һ�Ű����������Ϲ��Źع�����λ���Ա�
����������ɻ�ƿ�����ż�֧��ȸ�ᣬǽ��д�Ŵ���һ�����䡱�֣������
����Щ���ڽ����ϴ������ֽ�ϴ�����ˣ������������������ݣ�����������
���ȣ�һֱͨ����������ҡ�����ͨ������������߾Ϳ��Ե���԰�ˡ�
LONG
        );

        set("exits", ([
                "southdown" : __DIR__"dayuan",
                "enter"     : __DIR__"zoulang4",
                "westdown"  : __DIR__"zoulang2",
                "eastdown"  : __DIR__"zoulang5",
		"southeast" : __DIR__"wupinfang",
        ]));
        set("no_fight", 1);

        set("objects", ([
               __DIR__"npc/dizi1" : 1,
        ]));         

        setup();
}
