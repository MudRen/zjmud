//houyuan.c

inherit ROOM;

void create()
{
        set("short", "��Ժ");
        set("long", @LONG
���������ݵĺ�Ժ�ˣ����������˸����߲ˣ�������һ��ׯ�ڵأ�����
�����Χ��Ĳ�԰���������Ÿ����Ĳˣ���ʺ����ã�ҡҡ��׹�������Ǽ��
�����Ӵ����п��Լ����ɲ񵾲ݶѵ������ġ�
LONG
        );
	set("no_fight",1);
        set("exits", ([
               "east" : __DIR__"caiyuan",
               "west" : __DIR__"chaifang",
               "north" : __DIR__"caidi",
               "south" : __DIR__"shilu1",
        ]));
         
        setup();
}