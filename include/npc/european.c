// japanese name

#include "name.h"

mapping e_gname = ([
	"�޲���"   : "robert",
	"��ά��"   : "david",
	"�޵�"     : "rod",
	"������"   : "abel",
	"����"     : "kenny",
	"�����"   : "daniel",
	"����"     : "dave",
	"��ά��"   : "devin",
	"����"     : "don",
	"����"     : "white",
	"��³��"   : "brook",
	"�Ϳ�"     : "buck",
	"����˹"   : "charles",
	"����˹��" : "christ",
	"����˹�ж�": "christopher",
	"���︥��" : "clifford",
	"������"   : "clark",
	"����ά˹" : "elvis",
	"����"     : "ford",
	"����"     : "harry",
	"ϣ��"     : "hyman",
	"�ܿ�"     : "jack",
	"�ܷ�"     : "jeff",
	"Լ��"     : "john",
	"���ﰲ"   : "julian",
	"������"   : "lambert",
	"����˹"   : "max",
	"���˶�"   : "michael",
	"����"     : "william",
	"������"   : "philip",
]);

mapping e_sname = ([
	"Ƥ�˿�"     : "pycock",
	"������"     : "abbot",
	"��˼����"   : "aisbett",
	"�������˼" : "rigoutsos",
	"ά˹"       : "weiss",
	"������"     : "brady",
	"��˹����"   : "lustman",
	"�ȶ�����"   : "binford",
	"���ɵ�"     : "barnard",
	"����"       : "lamb",
	"��³˹�ٶ�" : "blostein",
	"��˼����"   : "fischler",
	"������"     : "eggert",
	"������˹"   : "faugeras",
	"������"     : "ettinger",
	"����ķѷ"   : "grimson",
	"���˹"     : "woods",
	"��ɭ"       : "hansen",
	"������"     : "hampel",
	"�������"   : "haralick",
	"���ߵ���"   : "nevatia",
	"����ά��"   : "sedgewick",
	"����˹��"   : "wechsler",
	"�ֶ���"     : "wolff",
]);

void generate_e_name(object ob)
{
	string name, pname1, pname2, id, id1, id2;
	pname1 = keys(e_gname)[random(sizeof(e_gname))];
	pname2 = keys(e_sname)[random(sizeof(e_sname))];
	id1 = e_gname[pname1];
	id2 = e_sname[pname2];
	name = pname1 + "��" + pname2;
	id = id1 + " " + id2;
	if (ob) ob->set_name(name, ({ id, id1, id2 }));
}
