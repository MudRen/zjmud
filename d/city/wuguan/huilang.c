//huilang.c by river

inherit ROOM;
void create()
{
        set("short", "����");
        set("long", @LONG
����һ�����ȣ��ȶ�����Ž��������ķ羰��ÿ��������ɫ�����Ӽ����
Ҳ�������ߵľ��룬���ɫ�������ߣ��ۻ�ɫ�ĵ�ש�����������棬Ѿ�ߡ�ū
����������ȥ����æ���Լ������飬������һ�㵡���������ܿ���һ��С��ͨ
���԰�ģ�������һ���ܳ������ȡ� 
LONG
        );
	set("no_fight",1);
        set("exits", ([
               "west" : __DIR__"zoulang7",
               "east" : __DIR__"xiaojing2",
        ]));
 
        setup();
}
