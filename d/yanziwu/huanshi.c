//ROOM: /d/yanziwu/huanshi.c

inherit ROOM;

void create()
{
	set("short", "��ʩˮ��");
	set("long",@LONG
����������ܣ����ϰ�������Ĺžɵ��鼮�����Ͼ����б�ǩ(sign)��
�����Ľ�����������������ռ����۶��ɵ���ѧ���⡣
LONG );
	set("exits", ([
	    "out": __DIR__"lanyue",
	]));
	set("objects", ([
	    "/clone/book/book-bamboo": random(2),
	    "/clone/book/book-iron": random(2),
	    "/clone/book/book-paper": random(2),
	    "/clone/book/book-silk": random(2),
	    "/clone/book/book-stone": random(2),
	]));
	set("item_desc",([
	    "sign" : "�󲿷��ܼ���������ˡ�\n"
	]));
	setup();
}
