// Room:/d/changan/road3.c

inherit  ROOM;

void  create()
{
	set("short", "��ٵ�");
	set("long", @LONG
����һ��������ֱ�Ĺٵ�������ݵ���ʮ���ۡ�����ͨ��
�ȹأ�������ֱ�ﳤ���ǡ�
LONG);
	set("exits",  ([  /*  sizeof()  ==  2  */
		"west" :  __DIR__"road4",
		"east" :  __DIR__"zhongnan",
	]));
	set("outdoors", "changan");
	setup();
}
