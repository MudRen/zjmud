// duan.h

int permit_recruit(object ob)
{
	if( ob->query("detach/���ϻ���") || ob->query("betrayer/���ϻ���") )
	{
		command("say ��Ȼ�뿪�����Ƕμң��Ͳ�Ҫ������");
		return 0;
	}
/*
	if (ob->query("born_family") != "���ϻ���")
	{
		command("shake");
		command("say ���Ƕμ��˻�������������ˣ�");
		return 0;
	}
*/
	return 1;
}
