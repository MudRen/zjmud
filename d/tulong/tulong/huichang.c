inherit ROOM;
void create()
{
	set("short", "�ﵶ�����᳡");
	set("long", @LONG
�������ﵶ�����᳡��һƬ��ݵ��ϰ����߰��ŷ��������˶��׵�һϯ�⣬ÿ
�����Զ��������ˣ��к�ɳ�ɡ��޾����ȭ�ŵȵȸ��ɵ��ӡ�
LONG );

	set("exits", ([
		"west" : __DIR__"gukou",
		]));

	set("objects", ([
		__DIR__"npc/mai" : 1,
		__DIR__"npc/guo" : 1,
		__DIR__"npc/yin" : 1,
		__DIR__"npc/yuan" : 1,
		__DIR__"obj/ding" : 1,
		__DIR__"npc/zhang" : 1,
		__DIR__"npc/chang" : 1,
		]));
	set("action_list", ([
		"����":"bi",
	]));
setup();
}


