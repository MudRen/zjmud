inherit ROOM;
void create()
{
	set("short", "������վ");
	set("long", @LONG
�����Ǹ������ݳǹٸ�����Ͱ��յ��ż��շ�����վ����վ���ſ���
����һ��ľ��(sign)������д��Щ�֡�

       ��ſ�Ҫ����Ϊ  squest��


LONG
	);
	set("item_desc", ([ /* sizeof() == 1 */
	    "sign" : "������֪��֮����Ϊ�����ż��շ����ң������ҷ����գ�\n"
	    "�����ʼ�һ������շ�����������ask officer about mail��\n",
]));
	set("exits", ([ /* sizeof() == 1 */
	       
		"west" : "/d/city/beimen",
	]));
	set("objects", ([
		__DIR__"npc/post_officer": 1
	]) );
	set("no_fight",1);
	setup();
}

