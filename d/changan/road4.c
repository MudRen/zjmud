// Room:/d/changan/road4.c

inherit  ROOM;

void  create  ()
{
	set("short",  "��ٵ�");
	set("long",  @LONG
����һ��������ֱ�Ĺٵ�������ݵ���ʮ���ۡ�����ͨ��
�ȹأ�������ֱ�ﳤ���ǡ�
LONG);
	set("exits",  ([  /*  sizeof()  ==  2  */
		"west" :  __DIR__"dong-chengmen",
		"east" :  __DIR__"road3",
	]));
	set("outdoors", "changan");
	setup();
}
